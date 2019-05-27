#include "Factory.h"

int main() {

	uint8_t ID[6] = { 1, 2, 3, 4, 5, 6 };

	Factory ourFactory(ID);

	for (uint8_t i = 0; i < 30; i++) {

		ourFactory.dispatchUnit(i + 7, i + 1);

		ourFactory.processUnit(4, 8, 5);
		ourFactory.processUnit(3, 2, 3);
		ourFactory.processUnit(2, 5, 6);
		ourFactory.processUnit(1, 4, 5);

		ourFactory.dispatchUnit(i + 5, i + 1);

		ourFactory.processUnit(4, 1, 4);
		ourFactory.processUnit(3, 4, 6);
		ourFactory.processUnit(2, 1, 8);
		ourFactory.processUnit(1, 1, 3);
	}

	int in, prev = 0;

	while (1) {
		ourFactory.updateCycle();

		in = OPCUA_readInt(ourFactory.client, "inputUnit");
		if (in != prev) {
			if (in) {
				cout << in << "\n";
			}
			prev = in;
		}
	}
}