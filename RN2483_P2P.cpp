#include <SoftwareSerial.h>
#include "RN2483_P2P.h"

SoftwareSerial lora(3, 4);

static void waitForResponse() 
{
	while (!lora.available()) 
		delay(100);
	while (lora.available())
		Serial.write(lora.read());
}

static void sendCmd(char *cmd)
{
	lora.write(cmd);
	lora.write("\r\n");
  
	waitForResponse();
}



void RN2483_init()
{
	lora.begin(57600); 
  
	waitForResponse();

	//sendCmd("sys factoryRESET");
	sendCmd("sys reset");
  
	sendCmd("radio set mod lora");
	sendCmd("radio set freq 868100000");
	sendCmd("radio set pwr 14");
	sendCmd("radio set sf sf7");
	sendCmd("radio set crc on");
	sendCmd("radio set cr 4/5");
	sendCmd("radio set wdt 0");
	sendCmd("radio set sync 12");
	sendCmd("radio set bw 500");
  
	sendCmd("mac pause");
}

void RN2483_sendData(byte data[], int size)
{
	lora.write( "radio tx " );

	for (int k=0; k<size ;k++)
	{
		lora.write( data[k] );
		Serial.write( data[k]);
	}

	lora.print("\r\n");

	waitForResponse();
}

void RN2483_receiveData()
{
	String str;
	
	lora.println("radio rx 0");

	str = lora.readStringUntil('\n');

	if ( str.indexOf("ok") == 0 ) 
	{
		str = lora.readStringUntil('\n');
		
		if ( str.length() > 1 ) 
		{        
			if ( str.indexOf("radio_rx") >= 0 ) 
			{           
				str = str.substring(10);             
              			Serial.print(str);          
			}
		}   
	}
}