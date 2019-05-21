#ifndef II_CONVEYOR_H
#define II_CONVEYOR_H

#include <iostream>
#include <queue>
#include <vector>
#include "opcua.h"
//#include "Unit.h"
#include "random.h"
using namespace std;

#define A 0
#define B 1
#define C 1

class Conveyor {
public:
	//void takeIn(Unit unit);
	virtual void process();
};

class MachineConveyor : Conveyor {
public:
	uint8_t type;
	queue <bool> machineOpQueue;
	queue <uint8_t> toolMachine;
	queue <uint8_t> toolTime;

	MachineConveyor(uint8_t init);

	void process(uint8_t bUnit, uint8_t fUnit);
};

class PusherConveyor : Conveyor {
public:
	uint8_t roller;
	queue <bool> pusherQueue;

	PusherConveyor(uint8_t init);

	void process(uint8_t objRoller);
};
/*
class WarehouseConveyor : Conveyor {
public:
	void process();
};*/

class RotatingConveyor : Conveyor {
public:
	uint8_t cellSelector;
	queue <bool> rotatorQueue;
	
	RotatingConveyor(uint8_t init);

	void process(uint8_t objCell);
};

#endif // II_CONVEYOR_H

