#include "opcua.h"
#include "operations.h"

int main() {


	UA_Client* client = OPCUA_connect();

	OPCUA_writeInt(client, "outputUnit", 0);

	for (uint8_t i = 0; i < 3; i++) {
		singleOperation(1, 5, 6);
		singleOperation(1, 2, 3);
		singleOperation(1, 2, 3);
	}

	//print_queue();

	while (1) {

		updateAction(client);

		updateQueue(client);
		
	}

	return 0;
}