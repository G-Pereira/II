#include "Factory.h"
#include "tinyxml2.h"
#include <iostream>
#include <stdio.h> 
#include <stdlib.h> 
//#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
//#include <sys/socket.h> 
//#include <arpa/inet.h> 
//#include <netinet/in.h> 

Factory::Factory(uint8_t cellID[6]) : endCell(cellID[4]), topCell(cellID[5]), client(connectPLC()) {
	for (int i = 0; i < 4; i++)
		prodCell.push_back(ProductionCell(cellID[i]));
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

	int in = OPCUA_readInt(client, "inputUnit");
	int ordID = OPCUA_readInt(client, "inputOrder");

	if (RE((bool)in, 19)) {// RE 19
		warehouse[in - 1]++;

		for(Order *ord : pOrders) {
			if(ord->id == ordID) {
				ord->numDoing--;
				ord->numDone++;

				if(ord->numDone == ord->quantity) {
					ord->endTime = time(NULL);

					// TODO: send order to database

					auto i = &ord - &orders[0];
					pOrders.erase(pOrders.begin()+i);
					delete ord;
				}

				break;
			}
		}
	}
	
	int unitR1 = OPCUA_readInt(client, "unitR1");
	int unitR2 = OPCUA_readInt(client, "unitR2");
	int unitR3 = OPCUA_readInt(client, "unitR3");

	int orderR1 = OPCUA_readInt(client, "orderR1");
	int orderR2 = OPCUA_readInt(client, "orderR2");
	int orderR3 = OPCUA_readInt(client, "orderR3");

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
#define PORT    54321 
#define MAXLINE 1024 
int8_t Factory::recvOrdersFile() {
	/*
	int sockfd; 
    char buffer[MAXLINE]; 
    char *hello = "Hello from server"; 
    struct sockaddr_in servaddr, cliaddr; 
      
    // Creating socket file descriptor 
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    } 
      
    memset(&servaddr, 127.0.0.1, sizeof(servaddr)); 
    memset(&cliaddr, 127.0.0.1, sizeof(cliaddr)); 
      
    // Filling server information 
    servaddr.sin_family    = AF_INET; // IPv4 
    servaddr.sin_addr.s_addr = INADDR_ANY; 
    servaddr.sin_port = htons(PORT); 
      
    // Bind the socket with the server address 
    if ( bind(sockfd, (const struct sockaddr *)&servaddr,  
            sizeof(servaddr)) < 0 ) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 
      
    int len, n; 
    n = recvfrom(sockfd, (char *)buffer, MAXLINE,  
                MSG_WAITALL, ( struct sockaddr *) &cliaddr, 
                (unsigned int*) &len); 
    buffer[n] = '\0'; 
    printf("Client : %s\n", buffer); 
    sendto(sockfd, (const char *)hello, strlen(hello),  
        MSG_CONFIRM, (const struct sockaddr *) &cliaddr, 
            len); 
    printf("Hello message sent.\n");  
	*/
	return 0;	// TODO
}

// Creates the Order objects from the XML file
int8_t Factory::createXMLOrders() {
	tinyxml2::XMLDocument ordersFile;
	tinyxml2::XMLElement *xmlRoot, *xmlOrder, *xmlRequestStores, *xmlTransform, *xmlUnload;
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

			pOrders.push_back(new ProcessingOrder((uint8_t)ordNum, (uint8_t)unitType, (uint8_t)finalType, (uint8_t)quantity));
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

			uOrders.push_back(new UnloadingOrder((uint8_t)ordNum, (uint8_t)unitType, (uint8_t)destPusher, (uint8_t)quantity));
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
	recvOrdersFile();							// TODO: check return codes
	createXMLOrders();
	//remove("orders.xml");

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
		// TODO: change quantities and times on order class
		if(ord->numDoing + ord->numDone == 0)
			ord->startTime = time(NULL);

		ord->numDoing++;

		switch(minCell) {
		case 0: case 2:
			if(minAvailability > 1) prodCell[minCell].generalAvailability++;
			else if(topMach == 'A') prodCell[minCell].generalAvailability = 4;
			else prodCell[minCell].generalAvailability++;
			break;

		case 1: case 3:
			if(minAvailability == 0 && topMach == 'A') prodCell[minCell].generalAvailability = 2;
			else prodCell[minCell].generalAvailability++;
			break;
		}

		processUnit(minCell+1, ord->unitType, ord->finalType, ord->id);

		return true;
	}

	return false;
}

bool Factory::processUOrder(UnloadingOrder* ord) {
	return false;	// TODO
}

// Decides which Unit should be sent next according to the pending orders and cells availabilities
void Factory::pollOrders() {			// TODO: check if valid transformation
	int i, j;

	if(!workUnit.size()) {
		// First check if there is a unit that can be immediatly serviced
		i = 0; j = 0;
		for(bool orderType : ordersSequence) {
			if(orderType) {	// Processing Order
				if(warehouse[pOrders[i]->unitType] > 0)
					if(processPOrder(pOrders[i], 0)) return;

				i++;
			}
			else {			// Unloading Order
				if(warehouse[uOrders[j]->unitType] > 0)
					if(processUOrder(uOrders[j])) return;
				
				j++;
			}
		}

		// If there is no unit that can be serviced then check if there is enough space in the cells to keep the next unit 
		i = 0; j = 0;
		for(bool orderType : ordersSequence) {
			if(orderType) {	// Processing Order
				if(processPOrder(pOrders[i++], 1)) return;
			}
			else {			// Unloading Order
				if(processUOrder(uOrders[j++])) return;
			}
		}
	}
}
