#ifndef II_ORDER_H
#define II_ORDER_H

#include <iostream>
#include <ctime>

class Order{
public:
	uint8_t id;
	time_t inTime;
	time_t startTime;
	time_t endTime;
	uint8_t type;

	void process();

private:

};

#endif //II_ORDER_H