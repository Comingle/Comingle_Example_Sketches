// Include the OS Sex software. This will create the 'Toy' object that you can
// use to interact with your toy.
#include <OSSex.h>

void setup()
{
	// Tell OSSex which toy we're using (All Multivibes are 0)
	Toy.setID(0);
}

void loop()
{
	// Set output 0 (the first motor) to turn on to a power of 200
	Toy.setOutput(0, 200);
	
	// wait for 500 milliseconds / half a second
	delay(500);
	
	// Set output 0 to a power of 0 (off);
	Toy.setOutput(0, 0);
	
	// wait another half second
	delay(500);
}

