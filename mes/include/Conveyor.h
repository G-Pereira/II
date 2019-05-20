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

#endif // II_CONVEYOR_H
