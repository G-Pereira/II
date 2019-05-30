#include "Factory.h"

int main() {

	uint8_t ID[6] = { 1, 2, 3, 4, 5, 6 };

	Factory ourFactory(ID);

	for (uint8_t i = 0; i < 3; i++) {

		//ourFactory.dispatchUnit(i + 2, i + 1, 30 + i);

		//ourFactory.processUnit(4, 8, 5, 10);
		//ourFactory.processUnit(3, 2, 3, 11);
		//ourFactory.processUnit(2, 5, 6, 12);
		//ourFactory.processUnit(1, 4, 5, 13);

		//ourFactory.dispatchUnit(i + 5, i + 1, 45 + i);

		//ourFactory.processUnit(4, 1, 4, 14);
		//ourFactory.processUnit(3, 4, 6, 15);
		//ourFactory.processUnit(2, 1, 8, 16);
		//ourFactory.processUnit(1, 1, 3, 17);

		ourFactory.processUnit(4, 9, 6, 18);
		//ourFactory.processUnit(3, 9, 6, 19);
		ourFactory.processUnit(2, 9, 6, 20);
		//ourFactory.processUnit(1, 9, 6, 21);
		
		ourFactory.processUnit(4, 7, 9, 22);
		ourFactory.processUnit(2, 7, 9, 23);

		//--------------------------------\\

		//ourFactory.processUnit(4, 1, 6, 24);	// ERROR
		//ourFactory.processUnit(2, 1, 6, 24);	// ERROR

		//ourFactory.processUnit(4, 1, 9, 25);
		//ourFactory.processUnit(2, 1, 9, 25);

		//ourFactory.processUnit(4, 7, 5, 26);
		//ourFactory.processUnit(2, 7, 5, 26);

		//ourFactory.processUnit(4, 8, 6, 27);
		//ourFactory.processUnit(2, 8, 6, 27);

		//ourFactory.processUnit(4, 7, 6, 28);
		//ourFactory.processUnit(2, 7, 6, 28);

	}

	while (1) {
		ourFactory.updateCycle();
	}
}