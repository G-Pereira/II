#include <iostream>
#include <queue>
#include <vector>

using namespace std;

#define A 0
#define B 1
#define C 1

vector <queue <bool>> pusherQueue(3, queue<bool>());
vector <queue <bool>> rotatorQueue(4, queue<bool>());
vector <vector <queue <bool>>> machineOpQueue(4, vector <queue <bool>>(2));
vector <vector <queue <uint8_t>>> toolMachine(4, vector <queue <uint8_t>>(2));
vector <vector <queue <uint8_t>>> toolTime(4, vector <queue <uint8_t>>(2));

void go2cell(uint8_t cell) {

    if ((cell >= 1) && (cell <= 4)) {
        rotatorQueue[cell - 1].push(false);

        for (uint8_t c = 0; c < cell - 1; c++)
            rotatorQueue[c].push(true);
    } else {
        for (uint8_t c = 0; c < 4; c++)
            rotatorQueue[c].push(true);
    }
}

void pusher(uint8_t roller) {
    go2cell(0);

    if ((roller >= 1) && (roller <= 3)) {
        pusherQueue[roller - 1].push(true);

        for (uint8_t c = 0; c < roller - 1; c++)
            pusherQueue[c].push(false);
    } else {
        for (uint8_t c = 0; c < 3; c++)
            pusherQueue[c].push(false);
    }
}

void singleOperation(uint8_t cell, uint8_t bUnit, uint8_t fUnit){

    go2cell(cell);

    switch(cell){
        case 1: case 3:{
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
                    machineOpQueue[cell-1][A].push(false);
                    machineOpQueue[cell-1][B].push(false);
                }
            }
            break;
        }
        case 2: case 4:{
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
                case 8:{
                    machineOpQueue[cell - 1][A].push(false);
                    machineOpQueue[cell - 1][C].push(true);
                    if (fUnit == 9) {
                        toolMachine[cell - 1][C].push(3);
                        toolTime[cell - 1][C].push(8);
                    } break;
                }
                default: {
                    machineOpQueue[cell-1][A].push(false);
                    machineOpQueue[cell-1][B*C].push(false);
                }
            }
            break;
        }
        default:{
            machineOpQueue[cell-1][A].push(false);
            machineOpQueue[cell-1][B*C].push(false);
        }
    }
}


int main(){

    /*pusher(3);

    cout << pusherQueue[0].front() << "\n";
    cout << pusherQueue[1].front() << "\n";
    cout << pusherQueue[2].front() << "\n\n";
    */

    singleOperation(4,2,5);

    cout << "Rotator Forward:\n";
    cout << rotatorQueue[0].front() << " ";
    cout << rotatorQueue[1].front() << " ";
    cout << rotatorQueue[2].front() << " ";
    cout << rotatorQueue[3].front() << "\n\n";

    cout << "Machine Operation:\n";
    cout << machineOpQueue[0][A].front() << " ";
    cout << machineOpQueue[0][B].front() << "\n";
    cout << machineOpQueue[1][A].front() << " ";
    cout << machineOpQueue[1][C].front() << "\n";
    cout << machineOpQueue[2][A].front() << " ";
    cout << machineOpQueue[2][B].front() << "\n";
    cout << machineOpQueue[3][A].front() << " ";
    cout << machineOpQueue[3][C].front() << "\n\n";

    cout << "Tool:\n";
    cout << unsigned(toolMachine[0][A].front()) << " ";
    cout << unsigned(toolMachine[0][B].front()) << "\n";
    cout << unsigned(toolMachine[1][A].front()) << " ";
    cout << unsigned(toolMachine[1][C].front()) << "\n";
    cout << unsigned(toolMachine[2][A].front()) << " ";
    cout << unsigned(toolMachine[2][B].front()) << "\n";
    cout << unsigned(toolMachine[3][A].front()) << " ";
    cout << unsigned(toolMachine[3][C].front()) << "\n\n";

    cout << "Time:\n";
    cout << unsigned(toolTime[0][A].front()) << " ";
    cout << unsigned(toolTime[0][B].front()) << "\n";
    cout << unsigned(toolTime[1][A].front()) << " ";
    cout << unsigned(toolTime[1][C].front()) << "\n";
    cout << unsigned(toolTime[2][A].front()) << " ";
    cout << unsigned(toolTime[2][B].front()) << "\n";
    cout << unsigned(toolTime[3][A].front()) << " ";
    cout << unsigned(toolTime[3][C].front()) << "\n\n";

}