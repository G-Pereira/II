#include "Factory.h"

int main() {

	uint8_t ID[6] = { 1, 2, 3, 4, 5, 6 };

	Factory ourFactory(ID);
	
	ourFactory.recvOrders();
	for (int i = 0; i < ourFactory.pOrders.size(); i++)
		ourFactory.pOrders[i]->print();
	
	for (int i = 0; i < ourFactory.uOrders.size(); i++)
		ourFactory.uOrders[i]->print();


	while (true)
	{
		ourFactory.pollOrders();
		ourFactory.updateCycle();
	}
	
}
