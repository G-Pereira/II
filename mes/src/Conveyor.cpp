#include "Conveyor.h"

MachineConveyor::MachineConveyor(uint8_t init) {
	type = init;
}

void MachineConveyor::process(uint8_t bUnit, uint8_t fUnit) {

	switch (type) {
	case 1: {
		switch (bUnit) {
		case 1: {
			switch (fUnit) {
			case 2: {
				machineOpQueue.push(true);
				toolMachine.push(1);
				toolTime.push(10);
				break;
			}
			case 4: {
				machineOpQueue.push(true);
				toolMachine.push(2);
				toolTime.push(5);
				break;
			}
			case 7: {
				machineOpQueue.push(true);
				toolMachine.push(3);
				toolTime.push(20);
				break;
			}
			default: {}
			} break;
		}
		case 5: {
			if (fUnit == 6) {
				machineOpQueue.push(true);
				toolMachine.push(2);
				toolTime.push(3);
			} break;
		}
		case 9: {
			if (fUnit == 5) {
				machineOpQueue.push(true);
				toolMachine.push(3);
				toolTime.push(8);
			} break;
		}
		default: {
			machineOpQueue.push(false);
		}
		}
	case 2: {
		switch (bUnit) {
		case 2: {
			if (fUnit == 3) {
				machineOpQueue.push(true);
				toolMachine.push(1);
				toolTime.push(20);
			}break;
		}
		case 4: {
			if (fUnit == 5) {
				machineOpQueue.push(true);
				toolMachine.push(2);
				toolTime.push(20);
			} break;
		}
		default: {
			machineOpQueue.push(false);
		}
		}break;
	}
	case 3: {
		switch (bUnit) {
		case 2: {
			if (fUnit == 5) {
				machineOpQueue.push(true);
				toolMachine.push(1);
				toolTime.push(5);
			} break;
		}
		case 7: {
			if (fUnit == 8) {
				machineOpQueue.push(true);
				toolMachine.push(2);
				toolTime.push(8);
			} break;
		}
		case 8: {
			if (fUnit == 9) {
				machineOpQueue.push(true);
				toolMachine.push(3);
				toolTime.push(8);
			} break;
		}
		default: {
			machineOpQueue.push(false);
		}
		}break;
	}
	default: {
		machineOpQueue.push(false);
	}
	}
	}
}

PusherConveyor::PusherConveyor(uint8_t init) {
	roller = init;
}

void PusherConveyor::process(uint8_t objRoller) {

	if (objRoller == roller) {
		pusherQueue.push(true);
	}
	else if(objRoller > roller) {
		pusherQueue.push(false);
	}
}

RotatingConveyor::RotatingConveyor(uint8_t init) {
	cellSelector = init;
}

void RotatingConveyor::process(uint8_t objCell) {
		
	if (objCell == cellSelector) {
		rotatorQueue.push(false);
	}
	else if (objCell > cellSelector) {
		rotatorQueue.push(true);
	}
	
}