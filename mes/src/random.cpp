#include "random.h"

bool RE(bool BT, uint8_t n)
{
	if (!BT) { Z[n] = false; return false; }		//BT is LOW
	if (BT && !Z[n]) { Z[n] = true; return true; }	//Rising Edge of BT detected
	return false;									//BT is HIGH
}