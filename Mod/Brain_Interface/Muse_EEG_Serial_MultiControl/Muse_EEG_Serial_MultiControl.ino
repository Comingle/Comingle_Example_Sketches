/* Mod software
/* Public Domain - adapted from other processing and arduino sketches */
/*Example by Quitmeyer/Comingle, Dec 10, 2014
 * {♥} COMINGLE --  2014/12/04 -- Share Freely

This uses the MUSE eeg and gets information from a
processing sketch that reads the OSC messages and tells the motors what to do

Github repo for p5 sketch and latest version of this are at
https://github.com/Comingle/Comingle_Example_Sketches/tree/master/Mod/Brain_Interface
*/

#include <OSSex.h>

bool clicked = false;
#define LED_N_SIDE A2
#define LED_P_SIDE A3

int darkamount = 0;
int incomingByte;      // a variable to read incoming serial data into

int m0=0;
int m1=0;
int m2=40;

void setup() {
  // 0 for all Multivibes currently.
  Toy.setID(0);

  // Blip all the motors and flash the LED to show that everything is working and the device is on.
  startupSequence();

  
    Serial.begin(9600);
}
int prevValue=0;

void loop() {
  
  
   switch(GetFromSerial())
 {
 case '0':
 m0= GetFromSerial();
break;
 case '1':
 m1= GetFromSerial();
break;

 case '2':
 m2= GetFromSerial();
break;

 }

    Toy.setOutput(0,m0);
    Toy.setOutput(1,m1);
    Toy.setOutput(2,m2);

  
  /*
    // see if there's incoming serial data:
  if (Serial.available() > 0) {
    // read the oldest byte in the serial buffer:
    incomingByte = Serial.read();
    Toy.setOutput(0,incomingByte);
    Toy.setOutput(1,incomingByte-10);
        Toy.setOutput(2,incomingByte-50);

  }
  
  else{
       // Toy.setOutput(1,0);

  }
*/

}

// read the serial port
int GetFromSerial()
{
 while (Serial.available()<=0) {
 }
 return Serial.read();
}

// Cycle through all the outputs, turn the LED on and leave it on to show that we're on
void startupSequence() {
  int outs = Toy.device.outCount;
  int outInterval = 100 / outs;
  
  Toy.setLED(0,128);
    
  for (int i = 0; i < outs; i++) {
    Toy.setOutput(i, 100+outInterval*i);
    delay(100);
    Toy.setOutput(i, 0);
    delay(50);
  }
  for (int i = 0; i < 3; i++) {  
    Toy.setLED(0,0);
    delay(100);
    Toy.setLED(0,128);
    delay(100);
  }
}


