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

	/*
	If you want to know what the commands below mean, see the "RN2483 LoRa Technology Module Command Reference User's Guide"
	provided on the doc/ folder, or look for it directly on the Microchip official website;
	*/
	sendCmd("radio set mod lora");
	sendCmd("radio set freq 868100000"); // Here, we use the EU863 (863MHz to 870MHz) ISM band, but you can select another band.
	/*
	With a modulation bandwidth of 125kHz, the center frequency must be between 864.125MHz and 869.875MHz on EU863 band and
	between 433.175MHz and 434.665MHz for the EU433 band.
	*/
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