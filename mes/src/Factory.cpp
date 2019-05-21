#include "Factory.h"
#include "Order.h"
#include "tinyxml2.h"
#include <iostream>

Factory::Factory(){

}

int8_t Factory::recvOrdersFile() {
	return 0;
}

int8_t Factory::createXMLOrders() {
	tinyxml2::XMLDocument ordersFile;
	tinyxml2::XMLElement *xmlRoot, *xmlOrder, *xmlRequestStores, *xmlTransform, *xmlUnload;
	Order *ord;
	int ordNum, quantity, unitType, finalType, destPusher;
	const char *temp = nullptr;

	ordersFile.LoadFile("./orders.xml");			// TODO: check file name and return value
	//remove("orders.xml");

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

			ord = new ProcessingOrder((uint8_t)ordNum, (uint8_t)unitType, (uint8_t)finalType, (uint8_t)quantity);
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

uint8_t Factory::recvOrders() {
	recvOrdersFile();							// TODO: check return codes
	createXMLOrders();

	return 0;
}

