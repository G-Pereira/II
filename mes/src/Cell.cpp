#include "Cell.h"

Cell::Cell(uint8_t init) : type(init) {}

void Cell::process()
{
	return;
}

ProductionCell::ProductionCell(uint8_t init) : Cell(init) {}

void ProductionCell::singleOperation(uint8_t bUnit, uint8_t fUnit) {
	
	waitMachine.push(false);

	switch (type) {
	case 1: case 3: {
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

	switch (type) {
	case 1: case 3: {
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
}

void ProductionCell::machineSelector(int availability) {

	// Select Machine B in Cell 1 and 3 
	if ((type == 1) || (type == 3)) {
		if (machineOpQueueBC.front()) {
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
			else {	//utilizar está na frente da queue da última fila 
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

	// Select Machine A in Cell 2 and 4 
	else if ((type == 2) || (type == 4)) {
		if (machineOpQueueA.front()) {
			if (((availability & ~0xFFFB) && (availability & ~0xFFFD)) || wait) { // 0100 & 0010 - 1st and 2nd Free
				machineOpQueueAB1.push(false);
				machineOpQueueAB2.push(true);
				toolMachineQueueAB2.push(toolMachineQueueA.front());
				toolTimeQueueAB2.push(toolTimeQueueA.front());
				machineOpQueueA.pop();
				toolMachineQueueA.pop();
				toolTimeQueueA.pop();
			}
			else if (!(availability & ~0xFFFB) && (availability & ~0xFFFD)) { // !0100 & 0010 - 1st Free
				machineOpQueueAB1.push(true);
				machineOpQueueAB2.push(false);
				toolMachineQueueAB1.push(toolMachineQueueA.front());
				toolTimeQueueAB1.push(toolTimeQueueA.front());
				machineOpQueueA.pop();
				toolMachineQueueA.pop();
				toolTimeQueueA.pop();
			}
			else {
				machineOpQueueAB1.push(false);
				machineOpQueueAB2.push(true);
				toolMachineQueueAB2.push(toolMachineQueueA.front());
				toolTimeQueueAB2.push(toolTimeQueueA.front());
				machineOpQueueA.pop();
				toolMachineQueueA.pop();
				toolTimeQueueA.pop();
			}
		}
		else {
			machineOpQueueAB1.push(false);
			machineOpQueueAB2.push(false);
			machineOpQueueA.pop();
		}
	}
}

LoadingCell::LoadingCell(uint8_t init) : Cell(init) {}

void LoadingCell::process(uint8_t objRoller) {
	
	switch (objRoller) {
	case 1:
		pusherQueue1.push(true);
		break;
	case 2:
		pusherQueue1.push(false);
		pusherQueue2.push(true);
		break;
	case 3:
		pusherQueue1.push(false);
		pusherQueue2.push(false);
		pusherQueue3.push(true);
		break;
	case 4:
		pusherQueue1.push(false);
		pusherQueue2.push(false);
		pusherQueue3.push(false);
		break;
	default:
		pusherQueue1.push(false);
		pusherQueue2.push(false);
		pusherQueue3.push(false);
		break;
	}

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