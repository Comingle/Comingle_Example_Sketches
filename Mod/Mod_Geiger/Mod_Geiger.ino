
/* It's the end times. The world is a vast desolated scorched crumb. 
 * The only technology that has survived are Comingle's Sex Toys 
 * (probably because of the high quality silicone they use)
 * You are what's left of humanity 
 * The biggest enemies are loneliness and sexy radiation monsters
 * Use this example the program your dildo to help you detect 
 * if you are using your dildo to service
 * a real human, or servicing one of those RADIOBEASTS in disguise
 * COMINGLE - Here to help, even in the end times.
 *
 * Example by Quitmeyer/Comingle, Dec 10, 2014
 * {♥} COMINGLE --  2014/12/04 -- Share Freely
 */

#include <OSSex.h>

void setup() {
  // 0 for all Multivibes currently.
  Toy.setID(0);

  // Blip all the motors and flash the LED to show that everything is working and the device is on.
  startupSequence();s

  pinMode(Toy.device.inPins[1], INPUT);

  Serial.begin(9600);

}

void loop() {
 
  int sensorVal = digitalRead(Toy.device.inPins[1]);

//print out the value of the pushbutton
  Serial.println(sensorVal);
  
    if (sensorVal == LOW) {
    digitalWrite(13, LOW);
    
    Toy.setOutput(-1,255);
    delay(60);
  } 
  else {
    digitalWrite(13, HIGH);
    Toy.setOutput(-1,0);
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





