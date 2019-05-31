#include "Cell.h"

Cell::Cell(uint8_t init) : type(init) {}

void Cell::process()
{
	return;
}

void Cell::updateQueue()
{
	return;
}

void Cell::updateAction()
{
	return;
}

ProductionCell::ProductionCell(uint8_t init) : Cell(init) {}

void ProductionCell::singleOperation(uint8_t bUnit, uint8_t fUnit) {
	
	doubleOpSAC.push(false);
	waitMachine.push(false);

	switch (type) {
	case 1: case 3: {
		doubleOpSA.push(false);
		switch (bUnit) {
		case 1: {
			machineOpQueueA.push(true);
			machineOpQueueBC.push(false);
			switch (fUnit) {
			case 2: {
				toolMachineQueueA.push(1);
				toolTimeQueueA.push(10);
				break;
			}
			case 4: {
				toolMachineQueueA.push(2);
				toolTimeQueueA.push(5);
				break;
			}
			case 7: {
				toolMachineQueueA.push(3);
				toolTimeQueueA.push(20);
				break;
			}
			default: {}
			} break;
		}
		case 5: {
			machineOpQueueA.push(true);
			machineOpQueueBC.push(false);
			if (fUnit == 6) {
				toolMachineQueueA.push(2);
				toolTimeQueueA.push(3);
			} break;
		}
		case 9: {
			machineOpQueueA.push(true);
			machineOpQueueBC.push(false);
			if (fUnit == 5) {
				toolMachineQueueA.push(3);
				toolTimeQueueA.push(8);
			} break;
		}
		case 2: {
			machineOpQueueA.push(false);
			machineOpQueueBC.push(true);
			if (fUnit == 3) {
				toolMachineQueueBC.push(1);
				toolTimeQueueBC.push(20);
			} break;
		}
		case 4: {
			machineOpQueueA.push(false);
			machineOpQueueBC.push(true);
			if (fUnit == 5) {
				toolMachineQueueBC.push(2);
				toolTimeQueueBC.push(20);
			} break;
		}
		default: {
			machineOpQueueA.push(false);
			machineOpQueueBC.push(false);
		}
		}
		break;
	}
	case 2: case 4: {

		doubleOpD.push(false);
		doubleOpSC.push(false);

		switch (bUnit) {
		case 1: {
			machineOpQueueA.push(true);
			machineOpQueueBC.push(false);
			switch (fUnit) {
			case 2: {
				toolMachineQueueA.push(1);
				toolTimeQueueA.push(10);
				break;
			}
			case 4: {
				toolMachineQueueA.push(2);
				toolTimeQueueA.push(5);
				break;
			}
			case 7: {
				toolMachineQueueA.push(3);
				toolTimeQueueA.push(20);
				break;
			}
			default: {}
			} break;
		}
		case 5: {
			machineOpQueueA.push(true);
			machineOpQueueBC.push(false);
			if (fUnit == 6) {
				toolMachineQueueA.push(2);
				toolTimeQueueA.push(3);
			} break;
		}
		case 9: {
			machineOpQueueA.push(true);
			machineOpQueueBC.push(false);
			if (fUnit == 5) {
				toolMachineQueueA.push(3);
				toolTimeQueueA.push(8);
			} break;
		}
		case 2: {
			machineOpQueueA.push(false);
			machineOpQueueBC.push(true);
			if (fUnit == 5) {
				toolMachineQueueBC.push(1);
				toolTimeQueueBC.push(5);
			} break;
		}
		case 7: {
			machineOpQueueA.push(false);
			machineOpQueueBC.push(true);
			if (fUnit == 8) {
				toolMachineQueueBC.push(2);
				toolTimeQueueBC.push(8);
			} break;
		}
		case 8: {
			machineOpQueueA.push(false);
			machineOpQueueBC.push(true);
			if (fUnit == 9) {
				toolMachineQueueBC.push(3);
				toolTimeQueueBC.push(8);
			} break;
		}
		default: {
			machineOpQueueA.push(false);
			machineOpQueueBC.push(false);
		}
		}
		break;
	}
	default: {
		machineOpQueueA.push(false);
		machineOpQueueBC.push(false);
	}
	}
}

void ProductionCell::multipleOperation(uint8_t bUnit, uint8_t fUnit) {

	doubleOpSAC.push(false);

	switch (type) {
	case 1: case 3: {
		doubleOpSA.push(false);
		machineOpQueueA.push(true);
		machineOpQueueBC.push(true);
		switch (bUnit) {
		case 1: {
			switch (fUnit) {
			case 3: {
				toolMachineQueueA.push(1);
				toolTimeQueueA.push(10);
				toolMachineQueueBC.push(1);
				toolTimeQueueBC.push(20);
				waitMachine.push(false);
				break;
			}
			case 5: {
				toolMachineQueueA.push(2);
				toolTimeQueueA.push(5);
				toolMachineQueueBC.push(2);
				toolTimeQueueBC.push(20);
				waitMachine.push(false);
				break;
			}
			}
			break;
		}
		case 4: {
			if (fUnit == 6) {
				toolMachineQueueA.push(2);
				toolTimeQueueA.push(3);
				toolMachineQueueBC.push(2);
				toolTimeQueueBC.push(20);
				waitMachine.push(true);
			}
			break;
		}
		}
		break;
	}
	case 2: case 4: {

		doubleOpD.push(false);
		doubleOpSC.push(false);

		machineOpQueueA.push(true);
		machineOpQueueBC.push(true);
		switch (bUnit) {
		case 1: {
			switch (fUnit) {
			case 5: {
				toolMachineQueueA.push(1);
				toolTimeQueueA.push(10);
				toolMachineQueueBC.push(1);
				toolTimeQueueBC.push(5);
				waitMachine.push(false);
				break;
			}
			case 8: {
				toolMachineQueueA.push(3);
				toolTimeQueueA.push(20);
				toolMachineQueueBC.push(2);
				toolTimeQueueBC.push(8);
				waitMachine.push(false);
				break;
			}
			}
			break;
		}
		case 2: {
			if (fUnit == 6) {
				toolMachineQueueA.push(2);
				toolTimeQueueA.push(3);
				toolMachineQueueBC.push(1);
				toolTimeQueueBC.push(5);
				waitMachine.push(true);
				wait++;
			}
			break;
		}
		case 8: {
			if (fUnit == 5) {
				toolMachineQueueA.push(3);
				toolTimeQueueA.push(8);
				toolMachineQueueBC.push(3);
				toolTimeQueueBC.push(8);
				waitMachine.push(true);
				wait++;
			}
			break;
		}

		}
		break;
	}
	default: {
		machineOpQueueA.push(false);
		machineOpQueueBC.push(false);
		waitMachine.push(false);
	}
	}
}

void ProductionCell::sameMachineOperation(uint8_t bUnit, uint8_t fUnit) {

	waitMachine.push(false);
	doubleOpSAC.push(false);
	
	if ((type == 1) || (type == 3)) {

		if ((bUnit == 9) && (fUnit == 6)) {

			// A: 9 -> 5
			machineOpQueueA.push(true);
			toolMachineQueueA.push(3);
			toolTimeQueueA.push(8);

			// A: 5 -> 6
			machineOpQueueA.push(true);
			toolMachineQueueA.push(2);
			toolTimeQueueA.push(3);

			// B:
			machineOpQueueBC.push(false);

			doubleOpSA.push(true);
			doubleOpSA.push(false);

			waitMachine.push(false);
		}


	}
	else if ((type == 2) || (type == 4)) {

		if ((bUnit == 9) && (fUnit == 6)) {

			machineOpQueueA.push(true);

			// A1: 9 -> 5
			toolMachineQueueA.push(3);
			toolTimeQueueA.push(8);

			// A2: 5 -> 6
			toolMachineQueueA.push(2);
			toolTimeQueueA.push(3);

			// C:
			machineOpQueueBC.push(false);

			doubleOpD.push(true);
			doubleOpSC.push(false);

		}
		else if ((bUnit == 7) && (fUnit == 9)) {

			// C: 7 -> 8
			machineOpQueueBC.push(true);
			toolMachineQueueBC.push(2);
			toolTimeQueueBC.push(8);
			
			// C: 8 -> 9
			machineOpQueueBC.push(true);
			toolMachineQueueBC.push(3);
			toolTimeQueueBC.push(8);

			// A:
			machineOpQueueA.push(false);

			doubleOpD.push(false);

			doubleOpSC.push(true);
			doubleOpSC.push(false);
		}

	}

}

void ProductionCell::tripleOperation(uint8_t bUnit, uint8_t fUnit) {

	if ((type == 2) || (type == 4)) {

		if ((bUnit == 1) && (fUnit == 6)) {
			
			doubleOpSAC.push(false);

			waitMachine.push(true);
			wait++;

			doubleOpD.push(true);

			doubleOpSC.push(false);

			// A1: 1 -> 2
			machineOpQueueA.push(true);
			toolMachineQueueA.push(1);
			toolTimeQueueA.push(10);

			// C: 2 -> 5
			machineOpQueueBC.push(true);
			toolMachineQueueBC.push(1);
			toolTimeQueueBC.push(5);

			// A2: 5 -> 6
			toolMachineQueueA.push(2);
			toolTimeQueueA.push(3);
			
		}
		else if ((bUnit == 1) && (fUnit == 9)) {

			doubleOpSAC.push(false);

			waitMachine.push(false);

			doubleOpD.push(false);
			
			doubleOpSC.push(true);
			doubleOpSC.push(false);

			// A1/2: 1 -> 7
			machineOpQueueA.push(true);
			toolMachineQueueA.push(3);
			toolTimeQueueA.push(20);
			
			// C: 7 -> 8
			machineOpQueueBC.push(true);
			toolMachineQueueBC.push(2);
			toolTimeQueueBC.push(8);

			// C: 8 -> 9
			machineOpQueueBC.push(true);
			toolMachineQueueBC.push(3);
			toolTimeQueueBC.push(8);

		}
		else if ((bUnit == 7) && (fUnit == 5)) {

			doubleOpSAC.push(false);

			waitMachine.push(true);
			wait++;

			doubleOpD.push(false);

			doubleOpSC.push(true);
			doubleOpSC.push(false);

			// C: 7 -> 8
			machineOpQueueBC.push(true);
			toolMachineQueueBC.push(2);
			toolTimeQueueBC.push(8);

			// C: 8 -> 9
			machineOpQueueBC.push(true);
			toolMachineQueueBC.push(3);
			toolTimeQueueBC.push(8);

			//A2: 9 -> 5
			machineOpQueueA.push(true);
			toolMachineQueueA.push(3);
			toolTimeQueueA.push(8);

		}
		else if ((bUnit == 8) && (fUnit == 6)) {

			doubleOpSAC.push(true);
			//doubleOpSAC.push(false);

			waitMachine.push(true);
			waitMachine.push(false);
			wait++;

			doubleOpD.push(false);

			doubleOpSC.push(false);

			// C: 8 -> 9
			machineOpQueueBC.push(true);
			toolMachineQueueBC.push(3);
			toolTimeQueueBC.push(8);

			// A2: 9 -> 5
			machineOpQueueA.push(true);
			toolMachineQueueA.push(3);
			toolTimeQueueA.push(8);

			// A2: 5 -> 6
			toolMachineQueueA.push(2);
			toolTimeQueueA.push(3);
		}
		else if ((bUnit == 7) && (fUnit == 6)) {

		doubleOpSAC.push(true);

		waitMachine.push(true);
		waitMachine.push(false);
		wait++;

		doubleOpD.push(false);

		doubleOpSC.push(true);
		doubleOpSC.push(false);

		// C: 7 -> 8
		machineOpQueueBC.push(true);
		toolMachineQueueBC.push(2);
		toolTimeQueueBC.push(8);

		// C: 8 -> 9
		machineOpQueueBC.push(true);
		toolMachineQueueBC.push(3);
		toolTimeQueueBC.push(8);

		// A2: 9 -> 5
		machineOpQueueA.push(true);
		toolMachineQueueA.push(3);
		toolTimeQueueA.push(8);

		// A2: 5 -> 6
		toolMachineQueueA.push(2);
		toolTimeQueueA.push(3);
		}
	}

}

void ProductionCell::process(uint8_t bUnit, uint8_t fUnit) {
	
		if (((bUnit == 1) && (fUnit == 2)) ||
			((bUnit == 1) && (fUnit == 4)) ||
			((bUnit == 1) && (fUnit == 7)) ||
			((bUnit == 5) && (fUnit == 6)) ||
			((bUnit == 9) && (fUnit == 5)) ||
			((bUnit == 2) && (fUnit == 3)) ||
			((bUnit == 4) && (fUnit == 5)) ||
			((bUnit == 2) && (fUnit == 5)) ||
			((bUnit == 7) && (fUnit == 8)) ||
			((bUnit == 8) && (fUnit == 9))) {

			singleOperation(bUnit, fUnit);
		}

		else if (((bUnit == 1) && (fUnit == 3)) ||
				 ((bUnit == 1) && (fUnit == 5)) ||
				 ((bUnit == 4) && (fUnit == 6)) ||
				 ((bUnit == 1) && (fUnit == 5)) ||
				 ((bUnit == 1) && (fUnit == 8)) ||
				 ((bUnit == 2) && (fUnit == 6)) ||
				 ((bUnit == 8) && (fUnit == 5))) {

			multipleOperation(bUnit, fUnit);
		}

		else if (((bUnit == 9) && (fUnit == 6)) ||
				 ((bUnit == 7) && (fUnit == 9))) {
			sameMachineOperation(bUnit, fUnit);
		}

		else if (((bUnit == 1) && (fUnit == 6)) ||
				 ((bUnit == 1) && (fUnit == 9)) ||
			  	 ((bUnit == 7) && (fUnit == 5)) ||
				 ((bUnit == 8) && (fUnit == 6)) ||
				 ((bUnit == 7) && (fUnit == 6))) {
			tripleOperation(bUnit, fUnit);
		}
}

void ProductionCell::machineSelector(UA_Client* client) {

	// Select Machine B in Cell 1 and 3 
	if ((type == 1) || (type == 3)) {

		char sf[20], av[20];
		sprintf_s(sf, 10, "C%dT4_sf", type);
		sprintf_s(av, 10, "C%d_av", type);

		if (RE(OPCUA_readBool(client, sf), type)) { // RE 1 and 3
			if (machineOpQueueBC.front()) {
				
				int availability = OPCUA_readInt(client, av);

				if ((availability & ~0xFFF7) && (availability & ~0xFFFB)) { // 1000 & 0100 - 1st and 2nd Free
					machineOpQueueAB1.push(false);
					machineOpQueueAB2.push(true);
					toolMachineQueueAB2.push(toolMachineQueueBC.front());
					toolTimeQueueAB2.push(toolTimeQueueBC.front());
					machineOpQueueBC.pop();
					toolMachineQueueBC.pop();
					toolTimeQueueBC.pop();
				}
				else if (!(availability & ~0xFFF7) && (availability & ~0xFFFB)) { // !1000 & 0100 - 1st Free
					machineOpQueueAB1.push(true);
					machineOpQueueAB2.push(false);
					toolMachineQueueAB1.push(toolMachineQueueBC.front());
					toolTimeQueueAB1.push(toolTimeQueueBC.front());
					machineOpQueueBC.pop();
					toolMachineQueueBC.pop();
					toolTimeQueueBC.pop();
				}
				else {
					machineOpQueueAB1.push(false);
					machineOpQueueAB2.push(true);
					toolMachineQueueAB2.push(toolMachineQueueBC.front());
					toolTimeQueueAB2.push(toolTimeQueueBC.front());
					machineOpQueueBC.pop();
					toolMachineQueueBC.pop();
					toolTimeQueueBC.pop(); 
				}
			}
			else {
				machineOpQueueAB1.push(false);
				machineOpQueueAB2.push(false);
				machineOpQueueBC.pop(); 
			}
		}
	}

	// Select Machine A in Cell 2 and 4 
	else if ((type == 2) || (type == 4)) {

		char sf[20], av[20];
		sprintf_s(sf, 10, "C%dT3_sf", type);
		sprintf_s(av, 10, "C%d_av", type);

		if (RE(OPCUA_readBool(client, sf), type)) { // RE 2 and 4
			if (machineOpQueueA.front()) { 
				int availability = OPCUA_readInt(client, av);

				if ((((availability & ~0xFFFB) && (availability & ~0xFFFD)) || wait) && !doubleOpD.front()) { // 0100 & 0010 - 1st and 2nd Free
					machineOpQueueAB1.push(false);
					machineOpQueueAB2.push(true);
					toolMachineQueueAB2.push(toolMachineQueueA.front());
					toolTimeQueueAB2.push(toolTimeQueueA.front());
					machineOpQueueA.pop();
					toolMachineQueueA.pop();
					toolTimeQueueA.pop();
					cout << "OPA2\t";

					if (doubleOpSAC.front())
					{
						machineOpQueueAB2.push(true);
						toolMachineQueueAB2.push(toolMachineQueueA.front());
						toolTimeQueueAB2.push(toolTimeQueueA.front());
						toolMachineQueueA.pop();
						toolTimeQueueA.pop();
						doubleOpAW.push(true);
						doubleOpAW.push(false);
						cout << "2x OPA2\t";
					}
					else
						doubleOpAW.push(false);
						
					cout << "\n";

					doubleOpSAC.pop();
					doubleOpD.pop();
				}
				else if ((!(availability & ~0xFFFB) && (availability & ~0xFFFD)) && !doubleOpD.front()) { // !0100 & 0010 - 1st Free
					machineOpQueueAB1.push(true);
					machineOpQueueAB2.push(false);
					toolMachineQueueAB1.push(toolMachineQueueA.front());
					toolTimeQueueAB1.push(toolTimeQueueA.front());
					machineOpQueueA.pop();
					toolMachineQueueA.pop();
					toolTimeQueueA.pop();

					cout << "OPA1\n";

					doubleOpSAC.pop();
					doubleOpD.pop();
					doubleOpAW.push(false);
				}
				else if (doubleOpD.front()) {
					machineOpQueueAB1.push(true);
					machineOpQueueAB2.push(true);
					toolMachineQueueAB1.push(toolMachineQueueA.front());
					toolTimeQueueAB1.push(toolTimeQueueA.front());
					toolMachineQueueA.pop();
					toolTimeQueueA.pop();
					toolMachineQueueAB2.push(toolMachineQueueA.front());
					toolTimeQueueAB2.push(toolTimeQueueA.front());
					toolMachineQueueA.pop();
					toolTimeQueueA.pop();

					cout << "OPA1\tOPA2\n";

					machineOpQueueA.pop();

					doubleOpSAC.pop();
					doubleOpD.pop();
					doubleOpAW.push(false);
				}
			}
			else {
				machineOpQueueAB1.push(false);
				machineOpQueueAB2.push(false);
				machineOpQueueA.pop();
				doubleOpD.pop();
				doubleOpSAC.pop();
				doubleOpAW.push(false);
				cout << "noOP\n";
			}
		}
	}
}

void ProductionCell::updateQueue(UA_Client* client) {
	
	if ((type == 1) || (type == 3)) {

	char t4[20], t5[20], t6[20];
	sprintf_s(t4, 10, "C%dT4_done", type);
	sprintf_s(t5, 10, "C%dT5_done", type);
	sprintf_s(t6, 10, "C%dT6_done", type);

		if (RE(OPCUA_readBool(client, t4), 10 + type * 2)) { // RE 12 and 16
			if (machineOpQueueA.front()) {
				toolMachineQueueA.pop();
				toolTimeQueueA.pop();
			}
			waitMachine.pop();
			machineOpQueueA.pop();
			doubleOpSA.pop();
		}

		if (RE(OPCUA_readBool(client, t5), 11 + type * 2)) { // RE 13 and 17
			if (machineOpQueueAB1.front()) {
				toolMachineQueueAB1.pop();
				toolTimeQueueAB1.pop();
			}
			machineOpQueueAB1.pop();
		}

		if (RE(OPCUA_readBool(client, t6), 12 + type * 2)) { // RE 14 and 18
			if (machineOpQueueAB2.front()) {
				toolMachineQueueAB2.pop();
				toolTimeQueueAB2.pop();
			}
			machineOpQueueAB2.pop();
		}
	}

	else if ((type == 2) || (type == 4)) {

	char t4[20], t5[20], t6[20];
	sprintf_s(t4, 10, "C%dT4_done", type);
	sprintf_s(t5, 10, "C%dT5_done", type);
	sprintf_s(t6, 10, "C%dT6_done", type);

		if (RE(OPCUA_readBool(client, t4), 20 + type * 2)) { // RE 24 and 28
			if (machineOpQueueAB1.front()) {
				toolMachineQueueAB1.pop();
				toolTimeQueueAB1.pop();
			}
			machineOpQueueAB1.pop();
		}

		if (RE(OPCUA_readBool(client, t5), 21 + type * 2)) { // RE 25 and 29
			if (machineOpQueueAB2.front()) {
				toolMachineQueueAB2.pop();
				toolTimeQueueAB2.pop();
			}

			machineOpQueueAB2.pop();

			if (waitMachine.front())
				wait--;

			waitMachine.pop();
			doubleOpAW.pop();
		}

		if (RE(OPCUA_readBool(client, t6), 22 + type * 2)) { // RE 26 and 30
			if (machineOpQueueBC.front()) {
				toolMachineQueueBC.pop();
				toolTimeQueueBC.pop();
			}
			machineOpQueueBC.pop();
			doubleOpSC.pop();
		}
	}
}

void ProductionCell::updateAction(UA_Client* client) {

	machineSelector(client);

	if ((type == 1) || (type == 3)) {

		char t4_op[20], t4_dt[20], t4_tt[20], t4_w[20];
		char t5_op[20], t5_dt[20], t5_tt[20];
		char t6_op[20], t6_dt[20], t6_tt[20];
		char doubleA[20];

		sprintf_s(t4_op, 10, "C%dT4_op", type);
		sprintf_s(t4_dt, 10, "C%dT4_dt", type);
		sprintf_s(t4_tt, 10, "C%dT4_tt", type);
		sprintf_s(t4_w, 10, "C%dT4_w", type);

		sprintf_s(t5_op, 10, "C%dT5_op", type);
		sprintf_s(t5_dt, 10, "C%dT5_dt", type);
		sprintf_s(t5_tt, 10, "C%dT5_tt", type);

		sprintf_s(t6_op, 10, "C%dT6_op", type);
		sprintf_s(t6_dt, 10, "C%dT6_dt", type);
		sprintf_s(t6_tt, 10, "C%dT6_tt", type);

		sprintf_s(doubleA, 10, "doubleA%d", type);

		if (machineOpQueueA.size())
			OPCUA_writeBool(client, t4_op, machineOpQueueA.front());
		else
			OPCUA_writeBool(client, t4_op, false);

		if (toolMachineQueueA.size())
			OPCUA_writeInt(client, t4_dt, toolMachineQueueA.front());

		if (toolTimeQueueA.size())
			OPCUA_writeInt(client, t4_tt, toolTimeQueueA.front());

		if (waitMachine.size())
			OPCUA_writeBool(client, t4_w, waitMachine.front());
		else
			OPCUA_writeBool(client, t4_w, 0);

		if (machineOpQueueAB1.size())
			OPCUA_writeBool(client, t5_op, machineOpQueueAB1.front());
		else
			OPCUA_writeBool(client, t5_op, false);

		if (toolMachineQueueAB1.size())
			OPCUA_writeInt(client, t5_dt, toolMachineQueueAB1.front());

		if (toolTimeQueueAB1.size())
			OPCUA_writeInt(client, t5_tt, toolTimeQueueAB1.front());

		if (machineOpQueueAB2.size())
			OPCUA_writeBool(client, t6_op, machineOpQueueAB2.front());
		else
			OPCUA_writeBool(client, t6_op, false);

		if (toolMachineQueueAB2.size())
			OPCUA_writeInt(client, t6_dt, toolMachineQueueAB2.front());

		if (toolTimeQueueAB2.size())
			OPCUA_writeInt(client, t6_tt, toolTimeQueueAB2.front());

		if (doubleOpSA.size())
			OPCUA_writeBool(client, doubleA, doubleOpSA.front());
		else
			OPCUA_writeBool(client, doubleA, false);

	}

	// Write in PLC for cell 2 and 4
	else if ((type == 2) || (type == 4)) {

		char t4_op[20], t4_dt[20], t4_tt[20];
		char t5_op[20], t5_dt[20], t5_tt[20], t5_w[20];
		char t6_op[20], t6_dt[20], t6_tt[20];
		char doubleC[20], doubleA[20];

		sprintf_s(t4_op, 10, "C%dT4_op", type);
		sprintf_s(t4_dt, 10, "C%dT4_dt", type);
		sprintf_s(t4_tt, 10, "C%dT4_tt", type);

		sprintf_s(t5_op, 10, "C%dT5_op", type);
		sprintf_s(t5_dt, 10, "C%dT5_dt", type);
		sprintf_s(t5_tt, 10, "C%dT5_tt", type);
		sprintf_s(t5_w, 10, "C%dT5_w", type);

		sprintf_s(t6_op, 10, "C%dT6_op", type);
		sprintf_s(t6_dt, 10, "C%dT6_dt", type);
		sprintf_s(t6_tt, 10, "C%dT6_tt", type);

		sprintf_s(doubleC, 10, "doubleC%d", type);
		sprintf_s(doubleA, 10, "doubleA%d", type);

	if (machineOpQueueAB1.size())
		OPCUA_writeBool(client, t4_op, machineOpQueueAB1.front());
	else
		OPCUA_writeBool(client, t4_op, false);

	if (toolMachineQueueAB1.size())
		OPCUA_writeInt(client, t4_dt, toolMachineQueueAB1.front());

	if (toolTimeQueueAB1.size())
		OPCUA_writeInt(client, t4_tt, toolTimeQueueAB1.front());

	if (machineOpQueueAB2.size())
		OPCUA_writeBool(client, t5_op, machineOpQueueAB2.front());
	else
		OPCUA_writeBool(client, t5_op, false);

	if (toolMachineQueueAB2.size())
		OPCUA_writeInt(client, t5_dt, toolMachineQueueAB2.front());

	if (toolTimeQueueAB2.size())
		OPCUA_writeInt(client, t5_tt, toolTimeQueueAB2.front());

	if (waitMachine.size())
		OPCUA_writeBool(client, t5_w, waitMachine.front());
	else 
		OPCUA_writeBool(client, t5_w, 0);

	if (machineOpQueueBC.size())
		OPCUA_writeBool(client, t6_op, machineOpQueueBC.front());
	else
		OPCUA_writeBool(client, t6_op, false);

	if (toolMachineQueueBC.size())
		OPCUA_writeInt(client, t6_dt, toolMachineQueueBC.front());

	if (toolTimeQueueBC.size())
		OPCUA_writeInt(client, t6_tt, toolTimeQueueBC.front());

	if(doubleOpSC.size())
		OPCUA_writeBool(client, doubleC, doubleOpSC.front());
	else 
		OPCUA_writeBool(client, doubleC, false);

	if (doubleOpAW.size())
		OPCUA_writeBool(client, doubleA, doubleOpAW.front());
	else
		OPCUA_writeBool(client, doubleA, false);

	}
}

LoadingCell::LoadingCell(uint8_t init) : Cell(init) {}

void LoadingCell::process(uint8_t objRoller) {

	switch (objRoller) {
	case 1:
		pusherQueue1.push(true);
		pushPend++;
		break;
	case 2:
		pusherQueue1.push(false);
		pusherQueue2.push(true);
		pushPend++;
		break;
	case 3:
		pusherQueue1.push(false);
		pusherQueue2.push(false);
		pusherQueue3.push(true);
		pushPend++;
		break;
	default:
		pusherQueue1.push(false);
		pusherQueue2.push(false);
		pusherQueue3.push(false);
		break;
	}

}

void LoadingCell::updateQueue(UA_Client* client) {

	if (RE(OPCUA_readBool(client, "C5T4_done"), 9)) // RE 9
		if (pusherQueue1.size()) {

			if (pusherQueue1.front())
				pushPend--;

			pusherQueue1.pop();
		}

	if (RE(OPCUA_readBool(client, "C5T5_done"), 10)) // RE 10
		if (pusherQueue2.size()) {

			if (pusherQueue2.front())
				pushPend--;

			pusherQueue2.pop();
		}

	if (RE(OPCUA_readBool(client, "C5T6_done"), 11)) // RE 11
		if (pusherQueue3.size()) {

			if (pusherQueue3.front())
				pushPend--;

			pusherQueue3.pop();

			if (pushBlock && !pushPend)
				pushBlock--;
		}

	if (RE(OPCUA_readBool(client, "loadReady"), 15)) // RE 15
		pushBlock++;
}

void LoadingCell::updateAction(UA_Client* client) {
	
	if (pusherQueue1.size())
		OPCUA_writeBool(client, "C5T4_ps", pusherQueue1.front());
	else 
		OPCUA_writeBool(client, "C5T4_ps", 0);

	if (pusherQueue2.size())
		OPCUA_writeBool(client, "C5T5_ps", pusherQueue2.front());
	else
		OPCUA_writeBool(client, "C5T5_ps", 0);

	if (pusherQueue3.size())
		OPCUA_writeBool(client, "C5T6_ps", pusherQueue3.front());
	else
		OPCUA_writeBool(client, "C5T6_ps", 0);

	OPCUA_writeBool(client, "notLoad", (bool)pushPend);
}

TransportationCell::TransportationCell(uint8_t init) : Cell(init) {}

void TransportationCell::process(uint8_t objCell) {

	switch (objCell) {
	case 1: 
		rotatorQueue1.push(false);
		break;
	case 2:
		rotatorQueue1.push(true);
		rotatorQueue2.push(false);
		break;
	case 3: 
		rotatorQueue1.push(true);
		rotatorQueue2.push(true);
		rotatorQueue3.push(false);
		break;
	case 4: 
		rotatorQueue1.push(true);
		rotatorQueue2.push(true);
		rotatorQueue3.push(true);
		rotatorQueue4.push(false);
		break;
	default: 
		rotatorQueue1.push(true);
		rotatorQueue2.push(true);
		rotatorQueue3.push(true);
		rotatorQueue4.push(true);
		break;
	}

}

void TransportationCell::updateQueue(UA_Client* client) {

		if (RE(OPCUA_readBool(client, "C1T2_done"), 5)) // RE 5
			rotatorQueue1.pop();

		if (RE(OPCUA_readBool(client, "C2T2_done"), 6)) // RE 6
			rotatorQueue2.pop();

		if (RE(OPCUA_readBool(client, "C3T2_done"), 7)) // RE 7
			rotatorQueue3.pop();

		if (RE(OPCUA_readBool(client, "C4T2_done"), 8)) // RE 8
			rotatorQueue4.pop();
}

void TransportationCell::updateAction(UA_Client* client) {

	if (rotatorQueue1.size())
		OPCUA_writeBool(client, "C1T2_f", rotatorQueue1.front());

	if (rotatorQueue2.size())
		OPCUA_writeBool(client, "C2T2_f", rotatorQueue2.front());

	if (rotatorQueue3.size())
		OPCUA_writeBool(client, "C3T2_f", rotatorQueue3.front());

	if (rotatorQueue4.size())
		OPCUA_writeBool(client, "C4T2_f", rotatorQueue4.front());
}