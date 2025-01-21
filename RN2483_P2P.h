#ifndef RN2483_P2P_H
#define RN2483_P2P_H

#include <Arduino.h>

void RN2483_init();
void RN2483_sendData(byte data[], int size);
void RN2483_receiveData();

#endif