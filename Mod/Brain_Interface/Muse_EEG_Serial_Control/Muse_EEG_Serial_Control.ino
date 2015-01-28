/* Multivibe software -- written by A Quitmeyer / Comingle. First released Dec 1, 2014 */
/* Public Domain - adapted from other processing and arduino sketches */
/* This software comes pre-loaded on Comingle Multivibe sex toys */

#include <OSSex.h>

bool clicked = false;
#define LED_N_SIDE A2
#define LED_P_SIDE A3

int darkamount = 0;
int incomingByte;      // a variable to read incoming serial data into

void setup() {
  // 0 for all Multivibes currently.
  Toy.setID(0);

  // Blip all the motors and flash the LED to show that everything is working and the device is on.
  startupSequence();

  
    Serial.begin(9600);
}
int prevValue=0;

void loop() {
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


