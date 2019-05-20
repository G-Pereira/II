#include "Factory.h"
#include "Order.h"
#include "tinyxml2.h"

Factory* Factory::instance = 0;

Factory* Factory::getInstance()
{
    if (instance == 0)
    {
        instance = new Factory();
    }

    return instance;
}

Factory::Factory(){

}

uint8_t Factory::recvOrders() {					// TODO: UML remove argument
	recvOrdersFile();
	createXMLOrders(this);
}

int8_t createXMLOrders(Factory *fac) {
	tinyxml2::XMLDocument ordersFile;
	tinyxml2::XMLElement *xmlRoot, *xmlOrder, *xmlRequestStores, *xmlTransform, *xmlUnload;
	Order *ord;
	int ordNum;

	ordersFile.LoadFile("orders.xml");			// TODO: check file name and return value
	remove("orders.xml");

	xmlRoot = ordersFile.FirstChild(); 
	if(xmlRoot == nullptr) return -1;

	xmlOrder = xmlRoot->FirstChildElement("Order");
	while(xmlOrder != nullptr) {
		xmlOrder->QueryIntAttribute("Number", &ordNum);

		xmlTransform = xmlOrder->FirstChildElement("Transform");
		if(xmlTransform != nullptr)
			ord = new ProcessingOrder(ordNum);

		xmlUnload = xmlOrder->FirstChildElement("Unload");
		if(xmlUnload != nullptr)
			ord = new UnloadingOrder(ordNum);

		fac->addOrder(ord);

		xmlOrder = xmlOrder->NextSiblingElement("Order");
	}

	xmlRequestStores = xmlRoot->FirstChildElement("Request_Stores");
	if(xmlRequestStores != nullptr)
		sendStorageReport(fac);

	return 0;
}

