#ifndef II_FACTORY_H
#define II_FACTORY_H

#include <iostream>
#include <vector>

#include "Order.h"
#include "Unit.h"
#include "Cell.h"

class Factory {
public:
	Factory();
    uint8_t recvOrders(std::ifstream file);
    void pollOrders();

private:
	std::vector<uint8_t> numUnits;
	std::vector<Order*> orders;
	std::vector<Cell*> cells;
	std::vector<Unit*> units;
};

#endif //II_FACTORY_H