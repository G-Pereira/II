#include "Factory.h"

Factory::Factory(uint8_t cellID[6]) 
	: cell1(cellID[0]), cell2(cellID[1]), cell3(cellID[2]), cell4(cellID[3]), endCell(cellID[4]), topCell(cellID[5]), client(connectPLC()) {}

UA_Client* Factory::connectPLC() {

	UA_Client* client = OPCUA_connect();
	OPCUA_writeInt(client, "outputUnit", 0);

	return client;
}
