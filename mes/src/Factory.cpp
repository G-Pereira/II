#include "Factory.h"
#include "tinyxml2.h"
#include <iostream>
#include <thread>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

Factory::Factory(uint8_t cellID[6]) : endCell(cellID[4]), topCell(cellID[5]), client(connectPLC()) {
	for (int i = 0; i < 4; i++)
		prodCell.push_back(ProductionCell(cellID[i]));
	
	db = Database();
}

UA_Client* Factory::connectPLC() {

	UA_Client* client = OPCUA_connect();
	OPCUA_writeInt(client, "outputUnit", 0);

	return client;
}

void Factory::processUnit(uint8_t cell, uint8_t bUnit, uint8_t fUnit, uint8_t orderNum) {

	topCell.process(cell);

	workUnit.push(bUnit);
	followUnit.push(fUnit);
	orderID.push(orderNum);
	
	warehouse[bUnit - 1]--;

	prodCell[cell-1].process(bUnit, fUnit);
}

void Factory::dispatchUnit(uint8_t sUnit, uint8_t objRoller, uint8_t orderNum) {

	workUnit.push(sUnit);
	followUnit.push(sUnit);
	orderID.push(orderNum);

	warehouse[sUnit - 1]--;

	topCell.process(0);
	endCell.process(objRoller);
}

void Factory::updateCycle() {

	if (RE(OPCUA_readBool(client, "AT1_done"), 0)) { // RE 0
		workUnit.pop();
		followUnit.pop();
		orderID.pop();
	}

	if ((workUnit.size())) {
		OPCUA_writeInt(client, "outputUnit", workUnit.front());
		OPCUA_writeInt(client, "finalUnit", followUnit.front());
		OPCUA_writeInt(client, "orderID", orderID.front());
	}
	else {
		OPCUA_writeInt(client, "outputUnit", 0);
		OPCUA_writeInt(client, "finalUnit", 0);
		OPCUA_writeInt(client, "orderID", 0);
	}

	inputUnit = OPCUA_readInt(client, "inputUnit");
	ordID = OPCUA_readInt(client, "inputOrder");

	if (RE((bool)inputUnit, 19)) {// RE 19
		warehouse[inputUnit - 1]++;

		db.orderUnitEnd(ordID);

		auto ordSeq = ordersSequence.begin();
		for(auto ord = pOrders.begin(); ord != pOrders.end(); ord++) {
			while(ordSeq != ordersSequence.end() && !*ordSeq) ordSeq++;

			if(ord->id == ordID) {
				ord->numDoing--;
				ord->numDone++;

				if(ord->numDone == ord->quantity) {
					ord->endTime = time(NULL);

					if(ordSeq != ordersSequence.end()) ordersSequence.erase(ordSeq);
					pOrders.erase(ord);
				}
				
				break;
			}

			ordSeq++;
		}
	}
	
	unitR1 = OPCUA_readInt(client, "unitR1");
	unitR2 = OPCUA_readInt(client, "unitR2");
	unitR3 = OPCUA_readInt(client, "unitR3");

	orderR1 = OPCUA_readInt(client, "orderR1");
	orderR2 = OPCUA_readInt(client, "orderR2");
	orderR3 = OPCUA_readInt(client, "orderR3");

	if(orderR1 > prevOrderR1) {
		for (int i = 0; i < uOrders.size(); i++) {
			if(uOrders[i].id == orderR1) {
				db.unloadUnit(1, uOrders[i].unitType);
				db.orderUnitEnd(orderR1);

				uOrders[i].numDoing--;
				uOrders[i].numDone++;
				break;
			}
		}
	}
	if(orderR2 > prevOrderR2) {
		for (int i = 0; i < uOrders.size(); i++) {
			if (uOrders[i].id == orderR2) {
				db.unloadUnit(2, uOrders[i].unitType);
				db.orderUnitEnd(orderR2);

				uOrders[i].numDoing--;
				uOrders[i].numDone++;
				break;
			}
		}
	}
	if(orderR3 > prevOrderR3) {
		for (int i = 0; i < uOrders.size(); i++) {
			if (uOrders[i].id == orderR3) {
				db.unloadUnit(3, uOrders[i].unitType);
				db.orderUnitEnd(orderR3);

				uOrders[i].numDoing--;
				uOrders[i].numDone++;
				break;
			}
		}
	}
	
	prevOrderR1 = orderR1;
	prevOrderR2 = orderR2;
	prevOrderR3 = orderR3;

	prodCell[0].updateQueue(client, &db);
	prodCell[1].updateQueue(client, &db);
	prodCell[2].updateQueue(client, &db);
	prodCell[3].updateQueue(client, &db);
	endCell.updateQueue(client);
	topCell.updateQueue(client);

	prodCell[0].updateAction(client);
	prodCell[1].updateAction(client);
	prodCell[2].updateAction(client);
	prodCell[3].updateAction(client);
	endCell.updateAction(client);
	topCell.updateAction(client);
}

// Creates the Order objects from the XML file
int8_t Factory::createXMLOrders() {
	tinyxml2::XMLDocument ordersFile;
	tinyxml2::XMLElement *xmlRoot, *xmlOrder, *xmlRequestStores, *xmlTransform, *xmlUnload;
	int ordNum, quantity, unitType, finalType, destPusher;
	const char *temp = nullptr;

	if(ordersFile.LoadFile("./orders.xml")) return 0;

	xmlRoot = ordersFile.FirstChildElement("ORDERS"); 
	if(xmlRoot == nullptr) return -1;

	xmlOrder = xmlRoot->FirstChildElement("Order");
	while(xmlOrder != nullptr) {

		xmlOrder->QueryIntAttribute("Number", &ordNum);

		xmlTransform = xmlOrder->FirstChildElement("Transform");
		if(xmlTransform != nullptr) {
			temp = xmlTransform->Attribute("From");
			unitType = atoi(temp+1);
			temp = nullptr;

			temp = xmlTransform->Attribute("To");
			finalType = atoi(temp+1);

			xmlTransform->QueryIntAttribute("Quantity", &quantity);

			pOrders.push_back(ProcessingOrder((uint8_t)ordNum, (uint8_t)unitType, (uint8_t)finalType, (uint8_t)quantity));
			db.orderInit(ordNum, quantity);
			ordersSequence.push_back(true);
		}

		xmlUnload = xmlOrder->FirstChildElement("Unload");
		if(xmlUnload != nullptr) {
			temp = xmlUnload->Attribute("Type");
			temp++;
			unitType = atoi(temp);
			temp = nullptr;

			temp = xmlUnload->Attribute("Destination");
			temp++;
			destPusher = atoi(temp);
			temp = nullptr;

			xmlUnload->QueryIntAttribute("Quantity", &quantity);

			uOrders.push_back(UnloadingOrder((uint8_t)ordNum, (uint8_t)unitType, (uint8_t)destPusher, (uint8_t)quantity));
			db.orderInit(ordNum, quantity);
			ordersSequence.push_back(false);
		}

		xmlOrder = xmlOrder->NextSiblingElement("Order");
	}

	xmlRequestStores = xmlRoot->FirstChildElement("Request_Stores");
	if(xmlRequestStores != nullptr)
		return 0; // TODO: sendStorageReport();

	return 0;
}

// Receives orders in the form of XML files (from UDP packets) and puts them in the appropriate objects
uint8_t Factory::recvOrders() {
	createXMLOrders();		// TODO: check return codes
	remove("orders.xml");

	return 0;
}

bool Factory::processPOrder(ProcessingOrder* ord, uint8_t enableStacking) {
	uint8_t possCell = possibleCells[ord->unitType-1][ord->finalType-1];
	char topMach = topMachine[ord->unitType-1][ord->finalType-1];
	uint8_t minAvailability = 9;
	uint8_t minCell;

	// Decide which cell the unit should be sent to
	for(int i = 3-(possCell%2); i >= 0; i -= 1+((possCell+1)/2)) {
		switch(topMach) {
		case 'A':
			if(prodCell[i].generalAvailability < 3+enableStacking && prodCell[i].generalAvailability < minAvailability) {
				minCell = i;
				minAvailability = prodCell[i].generalAvailability;
			}
			break;

		case 'B':
			if(prodCell[i].generalAvailability < 2+2*enableStacking && prodCell[i].generalAvailability < minAvailability) {
				minCell = i;
				minAvailability = prodCell[i].generalAvailability;
			}
			break;
			          
		case 'C':
			if(prodCell[i].generalAvailability < 1+3*enableStacking && prodCell[i].generalAvailability < minAvailability) {
				minCell = i;
				minAvailability = prodCell[i].generalAvailability;
			}
			break;
		}
	}
	
	// If it can send a unit then send it and update availabilities
	if(minAvailability < 9) {
		if((ord->numDoing + ord->numDone) == 0)
			db.orderStart(unsigned(ord->id));

		ord->numDoing++;

		switch(minCell) {
		case 0: case 2:
			if(minAvailability > 1) prodCell[minCell].generalAvailability++;
			else if(topMach == 'A') prodCell[minCell].generalAvailability = 4;
			else prodCell[minCell].generalAvailability++;
			break;

		case 1: case 3:
			if((minAvailability == 0) && (topMach == 'A')) prodCell[minCell].generalAvailability = 2;
			else prodCell[minCell].generalAvailability++;
			break;
		}

		db.orderUnitProcess(unsigned(ord->id));

		processUnit(minCell+1, ord->unitType, ord->finalType, ord->id);

		return true;
	}

	return false;
}

bool Factory::processUOrder(UnloadingOrder* ord) {// TODO: called when warehouse exit full!!! (and it shouldn't)

	// Find if there is enough room to send units to the destination pusher
	uint8_t availability = (endCell.pushAv >> (2*(ord->destinationPusher-1))) & 3;
	cout << "id: " << unsigned(ord->id) << "\tprevAv: " << unsigned(availability);
	for(auto tempOrd : uOrders)
		if(tempOrd.destinationPusher == ord->destinationPusher)
			availability += tempOrd.numDoing;
	cout << "\tpostAv: " << unsigned(availability) << endl;

	// If there is then send it and update the order's data accordingly
	if(availability < 3) {
		if (ord->numDoing + ord->numDone == 0)
			db.orderStart(unsigned(ord->id));

		ord->numDoing++;

		db.orderUnitProcess(unsigned(ord->id));

		dispatchUnit(ord->unitType, ord->destinationPusher, ord->id);

		return true;
	}

	return false;
}

// Decides which Unit should be sent next according to the pending orders and cells availabilities
void Factory::pollOrders() {			// TODO: check if valid transformation
	int i, j;

	if(!workUnit.size()) {
		// First check if there is a unit that can be immediatly serviced
		i = 0; j = 0;
		for(auto orderType = ordersSequence.begin(); orderType != ordersSequence.end(); orderType++) {
			if(*orderType) {	// Processing Order
				if((warehouse[pOrders[i].unitType-1] > 0) && (pOrders[i].quantity > (pOrders[i].numDoing + pOrders[i].numDone)))
					if(processPOrder(&pOrders[i], 0)) return;

				i++;
			}
			else {			// Unloading Order
				if((warehouse[uOrders[j].unitType-1] > 0) && (uOrders[j].quantity > (uOrders[j].numDoing + uOrders[j].numDone)))
					if(processUOrder(&uOrders[j])) return;
				
				j++;
			}
		}

		// If there is no unit that can be serviced then check if there is enough space in the cells to keep the next unit
		i = 0; j = 0;
		for (auto orderType = ordersSequence.begin(); orderType != ordersSequence.end(); orderType++) {
			if(*orderType){	// Processing Order
				if((warehouse[pOrders[i].unitType - 1] > 0) && (pOrders[i].quantity > (pOrders[i].numDoing + pOrders[i].numDone)))
					if(processPOrder(&pOrders[i], 1)) return;

				i++;
			}
			else {			// Unloading Order
				if((warehouse[uOrders[j].unitType - 1] > 0) && (uOrders[j].quantity > (uOrders[j].numDoing + uOrders[j].numDone)))
					if(processUOrder(&uOrders[j])) return;

				j++;
			}
		}
	}
}
