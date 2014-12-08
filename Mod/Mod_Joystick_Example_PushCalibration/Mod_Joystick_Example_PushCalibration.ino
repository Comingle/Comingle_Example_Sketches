#include <OSSex.h>

/* Hook up a a Joystick (made from two potentiometers) to Control
 * Press the button and wiggle the joystick to calibrate
 *
 * This example will be goo to modify for pretty much any-two sensor hookup
 * 
 * Example by Quitmyer/Comingle, Dec 9, 2014
 * {♥} COMINGLE --  2014/12/07 -- Share Freely
 */

int sensorAValue = 0;         // the sensor value
int sensorMin[] = {0,0};        // default values
int sensorMax[] = {1023,1023};           // default maximum sensor value

int sensorBValue = 0;         // the sensor value


int calibrationtime = 4000; // calibration for 4 seconds

int inputAnum=0; //Default the first input
int inputBnum=1;
boolean clicked= false;

void setup() {
  // 0 for all Multivibes currently.
  Toy.setID(0);

  // Blip all the motors and flash the LED to show that everything is working and the device is on.
  startupSequence();

  // Set up the button click handlers
  //This makes it so when we press our button, it will trigger the "click function"
  Toy.attachClick(click);


  Serial.begin(9600);

}

void loop() {

  if(clicked){
    //calibrate both axes
    calibration(inputAnum,calibrationtime); 
        calibration(inputBnum, calibrationtime); 
  }

  //Run the basic routine


  sensorAValue = Toy.getInput(0);
  sensorBValue = Toy.getInput(1);

  Serial.print("A (Vertical) ");
  Serial.print(sensorAValue);     //Note, we should address the confusion of how to address inputs 1 and 2
  Serial.print(" | ");
  Serial.print("B (Horizontal) ");
  Serial.print(sensorBValue);     //Note, we should address the confusion of how to address inputs 1 and 2
  Serial.print(" | ");
  
  //Scale the values by the min and max of calibration 

  int scaledreadingA=0;
  scaledreadingA= map(sensorAValue, sensorMin[0],sensorMax[0], 0, 255);
  int scaledreadingB=0;
  //Scale the potentiometer
  scaledreadingB= map(sensorBValue, sensorMin[1],sensorMax[1], 0, 255);

  Serial.print("Scaled Value (0-255) ");
  Serial.print(scaledreadingA);     //Note, we should address the confusion of how to address inputs 1 and 2
  Serial.print(" | ");
  
  Serial.print("Scaled Value (0-255) ");
  Serial.print(scaledreadingB);     //Note, we should address the confusion of how to address inputs 1 and 2
  Serial.print(" | ");
  Serial.println();


  //Make the motors run with the specified value
  Toy.setOutput(0,scaledreadingA);
  Toy.setOutput(1,scaledreadingB);

//Let's reading ports catchup
  delay(1);
}

void click() {
  clicked = true;
}

//Run the calibration sequence for the specified pin and specified amount of time
void calibration(int whichInput, long caltime){
    //Reset Min and Max for this calibration
    sensorMin[whichInput] = 1023;        // minimum sensor value
    sensorMax[whichInput] = 0;           // maximum sensor value
    int sensorValue=0;
   //Signal beginning of Calibration
Toy.setLED(0,0);

  Toy.setOutput(-1,0);
long timer = millis();

  // calibrate during the first five seconds 
  while (millis() < timer+caltime) {

    
    sensorValue = Toy.getInput(whichInput);

    // record the maximum sensor value
    if (sensorValue > sensorMax[whichInput]) {
      sensorMax[whichInput] = sensorValue;
    }

    // record the minimum sensor value
    if (sensorValue < sensorMin[whichInput]) {
      sensorMin[whichInput] = sensorValue;
    }
         Serial.print("Timer ");
  Serial.print(timer+caltime);     //Note, we should address the confusion of how to address inputs 1 and 2
  Serial.print(" | ");

     Serial.print("Millis ");
  Serial.print(millis());     //Note, we should address the confusion of how to address inputs 1 and 2
  Serial.print(" | ");

    
        Serial.print("Min Value ");
  Serial.print(sensorMin[whichInput]);     //Note, we should address the confusion of how to address inputs 1 and 2
  Serial.print(" | ");

  Serial.print("Max Value ");
  Serial.print(sensorMax[whichInput]);     //Note, we should address the confusion of how to address inputs 1 and 2
  Serial.print(" | ");
  Serial.println();
delay(2);
  }

  // signal the end of the calibration period
   Toy.setLED(0,0);
  startupSequence();
  clicked = false;
  

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









