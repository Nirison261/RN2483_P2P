#include <Arduino.h>
#include <RN2483_P2P.h>

void setup()
{
	Serial.begin(9600);
	RN2483_init();
}

void loop()
{
	RN2483_receiveData();
}
