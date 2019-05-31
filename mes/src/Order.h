#ifndef II_ORDER_H
#define II_ORDER_H

#include <iostream>
#include <ctime>

class Order{
public:
	uint8_t id;
	uint8_t unitType;

	time_t inTime;
	time_t startTime;
	time_t endTime;

    uint8_t quantity;
	uint8_t numDoing;
	uint8_t numDone;

	Order(uint8_t ordNum, uint8_t unitType, uint8_t quantity);
	virtual void print();
};

class ProcessingOrder : public Order {
public:
	uint8_t finalType;

	ProcessingOrder(uint8_t ordNum, uint8_t unitType, uint8_t finalType, uint8_t quantity);
	void print();
};

class UnloadingOrder : public Order {
public:
    uint8_t destinationPusher;

	UnloadingOrder(uint8_t ordNum, uint8_t unitType, uint8_t destPusher, uint8_t quantity);
	void print();
};

#endif //II_ORDER_H
