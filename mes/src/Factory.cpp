#include "Factory.h"
#include "tinyxml2.h"
#include <iostream>

Factory::Factory(uint8_t cellID[6]) : endCell(cellID[4]), topCell(cellID[5]), client(connectPLC()) {
	for (int i = 0; i < 4; i++)
		prodCell.push_back(ProductionCell(cellID[i]));
}

UA_Client* Factory::connectPLC() {

	UA_Client* client = OPCUA_connect();
	OPCUA_writeInt(client, "outputUnit", 0);

	return client;
}

void Factory::processUnit(uint8_t cell, uint8_t bUnit, uint8_t fUnit) {

	topCell.process(cell);

	workUnit.push(bUnit);
	followUnit.push(fUnit);
	
	prodCell[cell-1].process(bUnit, fUnit);
}

void Factory::dispatchUnit(uint8_t sUnit, uint8_t objRoller) {

	workUnit.push(sUnit);
	followUnit.push(sUnit);

	topCell.process(0);
	endCell.process(objRoller);
}

void Factory::updateCycle() {

	if (RE(OPCUA_readBool(client, "AT1_done"), 0)) { // RE 0
		workUnit.pop();
		followUnit.pop();
	}

	if ((workUnit.size())) {
		OPCUA_writeInt(client, "outputUnit", workUnit.front());
		OPCUA_writeInt(client, "finalUnit", followUnit.front());
	}
	else {
		OPCUA_writeInt(client, "outputUnit", 0);
		OPCUA_writeInt(client, "finalUnit", 0);
	}

	prodCell[0].updateQueue(client);
	prodCell[1].updateQueue(client);
	prodCell[2].updateQueue(client);
	prodCell[3].updateQueue(client);
	endCell.updateQueue(client);
	topCell.updateQueue(client);

	prodCell[0].updateAction(client);
	prodCell[1].updateAction(client);
	prodCell[2].updateAction(client);
	prodCell[3].updateAction(client);
	endCell.updateAction(client);
	topCell.updateAction(client);
}

// Receives the XML file containing the orders from UDP
int8_t Factory::recvOrdersFile() {
	return 0;	// TODO
}

// Creates the Order objects from the XML file
int8_t Factory::createXMLOrders() {
	tinyxml2::XMLDocument ordersFile;
	tinyxml2::XMLElement *xmlRoot, *xmlOrder, *xmlRequestStores, *xmlTransform, *xmlUnload;
	Order *ord;
	int ordNum, quantity, unitType, finalType, destPusher;
	const char *temp = nullptr;

	ordersFile.LoadFile("./orders.xml");			// TODO: check file name and return value

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

			ord = new Order((uint8_t)ordNum, (uint8_t)unitType, (uint8_t)finalType, (uint8_t)quantity);
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

			ord = new UnloadingOrder((uint8_t)ordNum, (uint8_t)unitType, (uint8_t)destPusher, (uint8_t)quantity);
		}

		orders.push_back(ord);

		xmlOrder = xmlOrder->NextSiblingElement("Order");
	}

	xmlRequestStores = xmlRoot->FirstChildElement("Request_Stores");
	if(xmlRequestStores != nullptr)
		return 0; //sendStorageReport();

	return 0;
}

// Receives orders in the form of XML files (from UDP packets) and puts them in the appropriate objects
uint8_t Factory::recvOrders() {
	recvOrdersFile();							// TODO: check return codes
	createXMLOrders();
	//remove("orders.xml");

	return 0;
}

// Decides which Unit should be sent next according to the pending orders and cells availabilities
void Factory::pollOrders() {			//TODO: check if there are units in the warehouse before sending / TODO: check if valid transformation
	if(/*warehouse exit variable says it's free*/) {
		// First check if there is a unit that can be immediatly serviced
		for(Order *ord : orders)					// TODO: check if the orders are being tested in the right order
			if(order.process(this, false))
				return;

		// If there is no unit that can be serviced then check if there is enough space in the cells to keep the next unit 
		for(Order *ord : orders)					// TODO: check if the orders are being tested in the right order
			if(order.process(this, true))
				return;
	}
}

