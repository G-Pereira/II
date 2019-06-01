#ifndef II_CELL_H
#define II_CELL_H

#include <iostream>
#include <queue>
#include <vector>
#include "opcua.h"
#include "random.h"

#include "Database.h"

using namespace std;

class Cell {
public:
	uint8_t type;

	Cell(uint8_t init);

	virtual void process();
	virtual void updateQueue();
	virtual void updateAction();
};

class ProductionCell : public Cell {
public:
	queue <bool> machineOpQueueA;
	queue <bool> machineOpQueueBC;
	queue <bool> machineOpQueueAB1;
	queue <bool> machineOpQueueAB2;

	queue <bool> waitMachine;
	int wait = 0;


	queue <bool> doubleOpD;
	queue <bool> doubleOpSC;
	queue <bool> doubleOpSA;
	queue <bool> doubleOpSAC;
	queue <bool> doubleOpAW;

	queue <uint8_t> toolMachineQueueA;
	queue <uint8_t> toolMachineQueueBC;
	queue <uint8_t> toolMachineQueueAB1;
	queue <uint8_t> toolMachineQueueAB2;
	
	queue <uint8_t> toolTimeQueueA;
	queue <uint8_t> toolTimeQueueBC;
	queue <uint8_t> toolTimeQueueAB1;
	queue <uint8_t> toolTimeQueueAB2;

	uint8_t generalAvailability;

	ProductionCell(uint8_t init);

	void singleOperation(uint8_t bUnit, uint8_t fUnit);
	
	void multipleOperation(uint8_t bUnit, uint8_t fUnit);

	void sameMachineOperation(uint8_t bUnit, uint8_t fUnit);

	void tripleOperation(uint8_t bUnit, uint8_t fUnit);

	void machineSelector(UA_Client* client);

	void process(uint8_t bUnit, uint8_t fUnit);

	void updateQueue(UA_Client* client, Database db);

	void updateAction(UA_Client* client);
};

class LoadingCell : public Cell {
public:
	queue <bool> pusherQueue1;
	queue <bool> pusherQueue2;
	queue <bool> pusherQueue3;
	queue <bool> rotatorQueueP;

	int pushAv = 0;

	LoadingCell(uint8_t init);

	void process(uint8_t objRoller);

	void updateQueue(UA_Client* client);

	void updateAction(UA_Client* client);
};

class TransportationCell : public Cell {
public:
	queue <bool> rotatorQueue1;
	queue <bool> rotatorQueue2;
	queue <bool> rotatorQueue3;
	queue <bool> rotatorQueue4;

	TransportationCell(uint8_t init);

	void process(uint8_t objCell);

	void updateQueue(UA_Client* client);

	void updateAction(UA_Client* client);
};

/*
class WarehouseConveyor : Conveyor {
public:
	void process();
};*/

#endif // II_CONVEYOR_H

