#ifndef II_UNLOADINGORDER_H
#define II_UNLOADINGORDER_H

#include <iostream>

#include "Order.h"

class UnloadingOrder : Order {
public:
	uint8_t quantity;
	uint8_t destinationPusher;

  void process();
};

#endif // II_UNLOADINGORDER_H
