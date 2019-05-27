#include "Factory.h"

int main() {

	uint8_t ID[6] = {1, 2, 3, 4, 5, 6};

	Factory ourFactory(ID);

	for(uint8_t i = 0; i < 3; i++) {
		ourFactory.processUnit(1, 1, 2);
	}

	while(1) {
		ourFactory.updateCycle();
	}
}