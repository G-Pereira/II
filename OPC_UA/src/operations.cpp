#include"operations.h"

vector <queue <bool>> pusherQueue(3, queue<bool>());
vector <queue <bool>> rotatorQueue(4, queue<bool>());
vector <vector <queue <bool>>> machineOpQueue(4, vector <queue <bool>>(2));
vector <vector <queue <bool>>> machineOpSelectorQueue(4, vector <queue <bool>>(2));
vector <vector <queue <uint8_t>>> toolMachine(4, vector <queue <uint8_t>>(2));
vector <vector <queue <uint8_t>>> toolSelectorQueue(4, vector <queue <uint8_t>>(2));
vector <vector <queue <uint8_t>>> toolTime(4, vector <queue <uint8_t>>(2));
vector <vector <queue <uint8_t>>> timeSelectorQueue(4, vector <queue <uint8_t>>(2));
queue <uint8_t> outUnit;

bool Z[6] = { true, true, true, true, true, true };

void print(void){

	//int Rot = rotatorQueue[0].size();

	int MAop = machineOpQueue[0][A].size();
	int MBop = machineOpQueue[0][B].size();

	int MB1 = machineOpSelectorQueue[0][B-1].size();
	int MB2 = machineOpSelectorQueue[0][B].size();

	//cout << "MAop: " << MAop << "\n";
	//cout << "\tMBop: " << MBop << "\n";
	cout << "MB1: " << MB1 << "\n";
	cout << "\tMB2: " << MB2 << "\n";

	//int TA = toolMachine[0][A].size();
	//int TB = toolMachine[0][B].size();

	//int TB1 = toolSelectorQueue[0][B-1].size();
	//int TB2 = toolSelectorQueue[0][B].size();

	//int tA = toolTime[0][A].size();
	//int tB = toolTime[0][A].size();

	//int tB1 = timeSelectorQueue[0][B-1].size();
	//int tB2 = timeSelectorQueue[0][B].size();

}


// Deteta o Rising Edge de uma entrada
bool RE(bool BT, uint8_t n)
{
	if (!BT) { Z[n] = false; return false; }		//BT is LOW
	if (BT && !Z[n]) { Z[n] = true; return true; }	//Rising Edge of BT detected
	return false;									//BT is HIGH
}

// Envia a infirmação necessária aos tapetes para
// deslocaram a paça seguinte para a cell desejada
void go2cell(uint8_t cell) {

	if ((cell >= 1) && (cell <= 4)) {
		rotatorQueue[cell - 1].push(false);

		for (uint8_t c = 0; c < cell - 1; c++)
			rotatorQueue[c].push(true);
	}
	else {
		for (uint8_t c = 0; c < 4; c++)
			rotatorQueue[c].push(true);
	}
}

// Indica o roller para o qual a próxima peça deve
// ser empurada
void pusher(uint8_t roller, uint8_t unit) {

	outUnit.push(unit);

	go2cell(0);

	if ((roller >= 1) && (roller <= 3)) {
		pusherQueue[roller - 1].push(true);

		for (uint8_t c = 0; c < roller - 1; c++)
			pusherQueue[c].push(false);
	}
	else {
		for (uint8_t c = 0; c < 3; c++)
			pusherQueue[c].push(false);
	}
}

// Dá todas as informações às máquinas (faz ou não operação,
// tipo de ferramenta e tempo a atuar) para operações simples 
// que devem ser executadas na peça seguinte
void singleOperation(uint8_t cell, uint8_t bUnit, uint8_t fUnit) {

	outUnit.push(bUnit);
	
	go2cell(cell);

	switch (cell) {
	case 1: case 3: {
		switch (bUnit) {
		case 1: {
			machineOpQueue[cell - 1][A].push(true);
			machineOpQueue[cell - 1][B].push(false);
			switch (fUnit) {
			case 2: {
				toolMachine[cell - 1][A].push(1);
				toolTime[cell - 1][A].push(10);
				break;
			}
			case 4: {
				toolMachine[cell - 1][A].push(2);
				toolTime[cell - 1][A].push(5);
				break;
			}
			case 7: {
				toolMachine[cell - 1][A].push(3);
				toolTime[cell - 1][A].push(20);
				break;
			}
			default: {}
			} break;
		}
		case 5: {
			machineOpQueue[cell - 1][A].push(true);
			machineOpQueue[cell - 1][B].push(false);
			if (fUnit == 6) {
				toolMachine[cell - 1][A].push(2);
				toolTime[cell - 1][A].push(3);
			} break;
		}
		case 9: {
			machineOpQueue[cell - 1][A].push(true);
			machineOpQueue[cell - 1][B].push(false);
			if (fUnit == 5) {
				toolMachine[cell - 1][A].push(3);
				toolTime[cell - 1][A].push(8);
			} break;
		}
		case 2: {
			machineOpQueue[cell - 1][A].push(false);
			machineOpQueue[cell - 1][B].push(true);
			if (fUnit == 3) {
				toolMachine[cell - 1][B].push(1);
				toolTime[cell - 1][B].push(20);
			} break;
		}
		case 4: {

			machineOpQueue[cell - 1][A].push(false);
			machineOpQueue[cell - 1][B].push(true);
			if (fUnit == 5) {
				toolMachine[cell - 1][B].push(2);
				toolTime[cell - 1][B].push(20);
			} break;
		}
		default: {
			machineOpQueue[cell - 1][A].push(false);
			machineOpQueue[cell - 1][B].push(false);
		}
		}
		break;
	}
	case 2: case 4: {
		switch (bUnit) {
		case 1: {
			machineOpQueue[cell - 1][A].push(true);
			machineOpQueue[cell - 1][C].push(false);
			switch (fUnit) {
			case 2: {
				toolMachine[cell - 1][A].push(1);
				toolTime[cell - 1][A].push(10);
				break;
			}
			case 4: {
				toolMachine[cell - 1][A].push(2);
				toolTime[cell - 1][A].push(5);
				break;
			}
			case 7: {
				toolMachine[cell - 1][A].push(3);
				toolTime[cell - 1][A].push(20);
				break;
			}
			default: {}
			} break;
		}
		case 5: {
			machineOpQueue[cell - 1][A].push(true);
			machineOpQueue[cell - 1][C].push(false);
			if (fUnit == 6) {
				toolMachine[cell - 1][A].push(2);
				toolTime[cell - 1][A].push(3);
			} break;
		}
		case 9: {
			machineOpQueue[cell - 1][A].push(true);
			machineOpQueue[cell - 1][C].push(false);
			if (fUnit == 5) {
				toolMachine[cell - 1][A].push(3);
				toolTime[cell - 1][A].push(8);
			} break;
		}
		case 2: {
			machineOpQueue[cell - 1][A].push(false);
			machineOpQueue[cell - 1][C].push(true);
			if (fUnit == 5) {
				toolMachine[cell - 1][C].push(1);
				toolTime[cell - 1][C].push(5);
			} break;
		}
		case 7: {
			machineOpQueue[cell - 1][A].push(false);
			machineOpQueue[cell - 1][C].push(true);
			if (fUnit == 8) {
				toolMachine[cell - 1][C].push(2);
				toolTime[cell - 1][C].push(8);
			} break;
		}
		case 8: {
			machineOpQueue[cell - 1][A].push(false);
			machineOpQueue[cell - 1][C].push(true);
			if (fUnit == 9) {
				toolMachine[cell - 1][C].push(3);
				toolTime[cell - 1][C].push(8);
			} break;
		}
		default: {
			machineOpQueue[cell - 1][A].push(false);
			machineOpQueue[cell - 1][B * C].push(false);
		}
		}
		break;
	}
	default: {
		machineOpQueue[cell - 1][A].push(false);
		machineOpQueue[cell - 1][B * C].push(false);
	}
	}
}

// Atribui uma máquina à peça quando há 2 máquinas iguais
void machineSelector(UA_Client* client) {

	// Select Machine B Cell 1
	if (RE(OPCUA_readBool(client, "C1T4_sf"), 5)) {
		//cout << "RE\t";
		if (machineOpQueue[0][B].front()) {
			//cout << "OP\t";
			int availability = OPCUA_readInt(client, "C1_av");

			if ((availability & ~0xFFF7) && (availability & ~0xFFFB)) { // 1000 & 0100 - 1st and 2nd Free
				machineOpSelectorQueue[0][B-1].push(false);
				machineOpSelectorQueue[0][B].push(true);
				toolSelectorQueue[0][B].push(toolMachine[0][B].front());
				timeSelectorQueue[0][B].push(toolTime[0][B].front());
				machineOpQueue[0][B].pop();
				toolMachine[0][B].pop();
				toolTime[0][B].pop();
				//cout << "GO 2\n";
			}
			else if (!(availability & ~0xFFF7) && (availability & ~0xFFFB)) { // 1000 & 0100 - 1st Free
				machineOpSelectorQueue[0][B-1].push(true);
				machineOpSelectorQueue[0][B].push(false);
				toolSelectorQueue[0][B-1].push(toolMachine[0][B].front());
				timeSelectorQueue[0][B-1].push(toolTime[0][B].front());
				machineOpQueue[0][B].pop();
				toolMachine[0][B].pop();
				toolTime[0][B].pop();
				//cout << "GO 1\n";
			}
			else {
				machineOpSelectorQueue[0][B-1].push(false);
				machineOpSelectorQueue[0][B].push(true);
				toolSelectorQueue[0][B].push(toolMachine[0][B].front());
				timeSelectorQueue[0][B].push(toolTime[0][B].front());
				machineOpQueue[0][B].pop();
				toolMachine[0][B].pop();
				toolTime[0][B].pop();
				//cout << "ELSE\n";
			}
		}
		else {
			machineOpSelectorQueue[0][B-1].push(false);
			machineOpSelectorQueue[0][B].push(false);
			machineOpQueue[0][B].pop();
			//cout << "NO OP\n";
		}
	}

}

// Atualiza a fila de ações assim que uma peça é "atuada"
void updateQueue(UA_Client* client) {

	// Update queues of cell 1
	if (RE(OPCUA_readBool(client, "AT1_done"), 0)) 
		outUnit.pop();

	if (RE(OPCUA_readBool(client, "C1T2_done"),1)) 
		rotatorQueue[0].pop();

	if (RE(OPCUA_readBool(client, "C1T4_done"),2)) {
		if (machineOpQueue[0][A].front()) {
			toolMachine[0][A].pop();
			toolTime[0][A].pop();
		}
		machineOpQueue[0][A].pop();
	}

	if (RE(OPCUA_readBool(client, "C1T5_done"),3)) {
		if (machineOpSelectorQueue[0][B-1].front()) {
			toolSelectorQueue[0][B-1].pop();
			timeSelectorQueue[0][B-1].pop();
		}
		machineOpSelectorQueue[0][B-1].pop();
	}

	if (RE(OPCUA_readBool(client, "C1T6_done"), 4)) {
		if (machineOpSelectorQueue[0][B].front()) {
			toolSelectorQueue[0][B].pop();
			timeSelectorQueue[0][B].pop();
		}
		machineOpSelectorQueue[0][B].pop();
	}
}

// Envia para o PLC a ação da próxima peça
void updateAction(UA_Client* client) {
	
	machineSelector(client);

	if (outUnit.size())
		OPCUA_writeInt(client, "outputUnit", outUnit.front());
	else 
		OPCUA_writeInt(client, "outputUnit", 0);

	if(rotatorQueue[0].size())
		OPCUA_writeBool(client, "C1T2_f", rotatorQueue[0].front());

	if (machineOpQueue[0][A].size())
		OPCUA_writeBool(client, "C1T4_op", machineOpQueue[0][A].front());
	else 
		OPCUA_writeBool(client, "C1T4_op", false);

	if (toolMachine[0][A].size())
		OPCUA_writeInt(client, "C1T4_dt", toolMachine[0][A].front());

	if (toolTime[0][A].size())
		OPCUA_writeInt(client, "C1T4_tt", toolTime[0][A].front());

	if (machineOpSelectorQueue[0][B-1].size())
		OPCUA_writeBool(client, "C1T5_op", machineOpSelectorQueue[0][B-1].front());
	else 
		OPCUA_writeBool(client, "C1T5_op", false);

	if (toolSelectorQueue[0][B-1].size())
		OPCUA_writeInt(client, "C1T5_dt", toolSelectorQueue[0][B-1].front());

	if (timeSelectorQueue[0][B-1].size())
		OPCUA_writeInt(client, "C1T5_tt", timeSelectorQueue[0][B-1].front());

	if (machineOpSelectorQueue[0][B].size())
		OPCUA_writeBool(client, "C1T6_op", machineOpSelectorQueue[0][B].front());
	else 
		OPCUA_writeBool(client, "C1T6_op", false);

	if (toolSelectorQueue[0][B].size())
		OPCUA_writeInt(client, "C1T6_dt", toolSelectorQueue[0][B].front());

	if (timeSelectorQueue[0][B].size())
		OPCUA_writeInt(client, "C1T6_tt", timeSelectorQueue[0][B].front());
}