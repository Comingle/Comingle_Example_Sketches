// Include the OS Sex software. This will create the 'Toy' object that you can
// use to interact with your toy.
#include <OSSex.h>




void setup()
{
	// Tell OSSex which toy we're using (All Multivibes are 0)
	Toy.setID(0);
  Serial.begin(9600);
}

void loop()
{
	// Set output 0 (the first motor) to turn on to a power of 200

int sensorValue = analogRead(A3);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  Serial.println(sensorValue-800);
	Toy.setOutput(0, sensorValue/4);
	
}

