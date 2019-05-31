#include "Factory.h"

int main() {

	uint8_t ID[6] = { 1, 2, 3, 4, 5, 6 };

	Factory ourFactory(ID);
	
	ourFactory.recvOrders();

	for(auto ord : ourFactory.pOrders)
		ord.print();

	for(auto ord : ourFactory.uOrders)
		ord.print();

	while (true)
	{
		ourFactory.pollOrders();
		ourFactory.updateCycle();
	}
	
}
