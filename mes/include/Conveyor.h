#ifndef II_CONVEYOR_H
#define II_CONVEYOR_H

#include "Unit.h"

class Conveyor{
public:
	void takeIn(Unit unit);
	bool checkAvailability();

  virtual void process();
private:
	
};

class MachineConveyor : Conveyor {
public:
	void process(Unit unit);

private:

};

class PusherConveyor : Conveyor {
public:
	void process();

private:

};

class WarehouseConveyor : Conveyor {
public:
	void process();

private:

};

class RotatingConveyor : Conveyor {
public:
	void process();

private:

};

#endif // II_CONVEYOR_H
