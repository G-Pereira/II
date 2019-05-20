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

class LoadingCell : Cell {
public:
	void process();

private:
	
};

class ProdutionCell : Cell {
public:
	void process(Unit uint);

private:
	
};

class TransportationCell : Cell {
public:
	void process();

private:
	
};

#endif // II_CELL_H
