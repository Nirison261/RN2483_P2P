#include <Arduino.h>
#include <RN2483_P2P.h>

byte data[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
byte wrongData[] = {'G', 'H', '!'};

void setup()
{
	Serial.begin(9600);
	RN2483_init();
}

void loop()
{
	RN2483_sendData(data, 16);
	delay(3000);
	RN2483_sendData(wrongData, 3);
	delay(3000);
}
