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

	Order(uint8_t ordNum, uint8_t unitType);
	virtual uint8_t process();
	virtual void print();
};

class ProcessingOrder : public Order {
public:
	uint8_t finalType;
	uint8_t quantity;

	ProcessingOrder(uint8_t ordNum, uint8_t unitType, uint8_t finalType, uint8_t quantity);
	void print();
};

class UnloadingOrder : public Order {
public:
    uint8_t destinationPusher;
    uint8_t quantity;

	UnloadingOrder(uint8_t ordNum, uint8_t unitType, uint8_t destPusher, uint8_t quantity);
	void print();
};

#endif //II_ORDER_H
