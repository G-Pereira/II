#ifndef II_CELL_H
#define II_CELL_H

#include <iostream>
#include <queue>
#include <vector>
using namespace std;

class Cell {
public:
	uint8_t type;
	//void takeIn(Unit unit);
	Cell(uint8_t init);

	virtual void process();
};

class ProductionCell : Cell {
public:
	queue <bool> machineOpQueueA;
	queue <bool> machineOpQueueBC;
	queue <bool> machineOpQueueAB1;
	queue <bool> machineOpQueueAB2;

	queue <bool> waitMachine;
	int wait = 0;

	queue <uint8_t> toolMachineQueueA;
	queue <uint8_t> toolMachineQueueBC;
	queue <uint8_t> toolMachineQueueAB1;
	queue <uint8_t> toolMachineQueueAB2;
	
	queue <uint8_t> toolTimeQueueA;
	queue <uint8_t> toolTimeQueueBC;
	queue <uint8_t> toolTimeQueueAB1;
	queue <uint8_t> toolTimeQueueAB2;

	ProductionCell(uint8_t init);

	void singleOperation(uint8_t bUnit, uint8_t fUnit);
	
	void multipleOperation(uint8_t bUnit, uint8_t fUnit);

	void machineSelector(int availability);

	void process(uint8_t bUnit, uint8_t fUnit);
};

class LoadingCell : Cell {
public:
	queue <bool> pusherQueue1;
	queue <bool> pusherQueue2;
	queue <bool> pusherQueue3;

	LoadingCell(uint8_t init);

	void process(uint8_t objRoller);
};

class TransportationCell : Cell {
public:
	queue <bool> rotatorQueue1;
	queue <bool> rotatorQueue2;
	queue <bool> rotatorQueue3;
	queue <bool> rotatorQueue4;

	TransportationCell(uint8_t init);

	void process(uint8_t objCell);
};

/*
class WarehouseConveyor : Conveyor {
public:
	void process();
};*/

#endif // II_CONVEYOR_H

