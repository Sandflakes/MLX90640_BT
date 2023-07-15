#include <Arduino.h>
#include <SoftwareSerial.h>
// #include <MLX90640_API.h>
// #include <MLX90640_I2C_Driver.h>

#define BUFFER_SIZE 10

bool echo = false;
char buff[BUFFER_SIZE];
String data;

SoftwareSerial BTserial(10, 11); // RX | TX

void setup()
{
    Serial.begin(115200);

	BTserial.begin(9600);

	// MLX90640_I2CInit();
	
    Serial.println("Setup done.");
}

void loop()
{
	if (BTserial.available())
	{
		size_t nBytes = BTserial.readBytes(buff, BUFFER_SIZE-1);
		Serial.println(nBytes);

		Serial.write(buff, nBytes);
		// BTserial.write(buff, nBytes);

		// for (size_t i = 0; i < nBytes; i++)
		// {
		// 	BTserial.print(buff[i]);
		// }	
	}
	// 	data = BTserial.readString();
		
	// 	for (size_t i = 0; i < data.length(); i++)
	// 	{
	// 		Serial.print(data[i]);
	// 	}
	// 	Serial.println(" end");
		
	// 	// if it is a command
	// 	if(data.length() == 1)
	// 	{
	// 		switch (tolower(data[0]))
	// 		{
	// 		case 'e':
	// 			echo = !echo;
	// 			BTserial.println(String("Toggle echo: " + String((echo ? "On" : "Off"))));
	// 			break;
	// 		default:
	// 			BTserial.println("ERR: Unknown Command");
	// 			break;
	// 		}
	// 	}
	// 	else if(data.length() > 1)
	// 	{
	// 		if(echo)
	// 			BTserial.println(data);
	// 	}
	// }
}