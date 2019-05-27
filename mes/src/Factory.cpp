#include "Factory.h"

Factory::Factory(uint8_t cellID[6]) 
	: cell1(cellID[0]), cell2(cellID[1]), cell3(cellID[2]), cell4(cellID[3]), endCell(cellID[4]), topCell(cellID[5]), client(connectPLC()) {}

UA_Client* Factory::connectPLC() {

	UA_Client* client = OPCUA_connect();
	OPCUA_writeInt(client, "outputUnit", 0);

	return client;
}

void Factory::processUnit(uint8_t cell, uint8_t bUnit, uint8_t fUnit) {

	topCell.process(cell);

	switch (cell) {
	case 1:
		cell1.process(bUnit, fUnit);
		break;
	case 2:
		cell2.process(bUnit, fUnit);
		break;
	case 3:
		cell3.process(bUnit, fUnit);
		break;
	case 4:
		cell4.process(bUnit, fUnit);
		break;
	}
}

void Factory::dispatchUnit(uint8_t objRoller) {

	topCell.process(0);
	endCell.process(objRoller);
}

void Factory::updateCycle() {

	cell1.updateQueue(client);
	cell2.updateQueue(client);
	cell3.updateQueue(client);
	cell4.updateQueue(client);
	endCell.updateQueue(client);
	topCell.updateQueue(client);

	cell1.updateAction(client);
	cell2.updateAction(client);
	cell3.updateAction(client);
	cell4.updateAction(client);
	endCell.updateAction(client);
	topCell.updateAction(client);
}