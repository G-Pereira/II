#ifndef II_CELL_H
#define II_CELL_H

#include <iostream>
#include <vector>

#include "Conveyor.h"

class Cell {
public:
	std::vector<Conveyor> conveyors;

	void takeIn(Unit* unit);
	bool checkAvalability();

  virtual void process();
private:

};

#endif // II_CELL_H
