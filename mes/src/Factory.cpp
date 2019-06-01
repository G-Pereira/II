#include "Factory.h"

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

	inputUnit = OPCUA_readInt(client, "inputUnit");
	inputOrder = OPCUA_readInt(client, "inputOrder");

	if (RE((bool)inputUnit, 19)) // RE 19
		warehouse[inputUnit - 1]++;
	
	unitR1 = OPCUA_readInt(client, "unitR1");
	unitR2 = OPCUA_readInt(client, "unitR2");
	unitR3 = OPCUA_readInt(client, "unitR3");

	orderR1 = OPCUA_readInt(client, "orderR1");
	orderR2 = OPCUA_readInt(client, "orderR2");
	orderR3 = OPCUA_readInt(client, "orderR3");

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