#ifndef II_PROCESSINGORDER_H
#define II_PROCESSINGORDER_H

#include <iostream>

#include "Order.h"

class ProcessingOrder : Order {
public:
	uint8_t quantity;
	uint8_t finalType;
};

#endif // II_PROCESSINGORDER_H