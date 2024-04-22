#ifndef RN2483_P2P_H
#define RN2483_P2P_H

#include <Arduino.h>

/*
Radio settings
==============

In Madagascar, the ISM bands are:
	- EU433 (433.05MHz to 434.79MHz)
	- EU863 (863MHz to 870MHz)

With a modulation bandwidth of 125kHz, the center frequency must be between 433.175MHz and 434.665MHz
on the EU433 band, and between 864.125MHz and 869.875MHz on EU863 band.

*/

void RN2483_init();
void RN2483_sendData(byte data[], int size);
void RN2483_receiveData();

#endif