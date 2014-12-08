#include <OSSex.h>

/* Hook up a Pot Knob to Control - this is like the easiest thing you can control it with
 * Press the main button, and automatically trigger a calibration sequence
 * Example by Quitmyer/Comingle, Dec 4, 2014
 * {♥} COMINGLE --  2014/12/04 -- Share Freely
 */


int sensorValue = 0;         // the sensor value
int sensorMin = 0;        // default values
int sensorMax = 1023;           // default maximum sensor value

int calibrationtime = 5000; // calibration for 4 seconds

int inputnum=0; //Default the first input

boolean clicked= false;

void setup() {
  // 0 for all Multivibes currently.
  Toy.setID(0);

  // Blip all the motors and flash the LED to show that everything is working and the device is on.
  startupSequence();

  // Set up the button click handlers
  //This makes it so when we press our button, it will trigger the "click function"
  Toy.attachClick(Click);

  Serial.begin(9600);

}

void loop() {
  if(clicked){
   calibration(inputnum,calibrationtime); 
  }
  
  sensorValue = Toy.getInput(inputnum);


  Serial.print("potentiometer Value ");
  Serial.print(sensorValue);     //Note, we should address the confusion of how to address inputs 1 and 2
  Serial.print(" | ");

  int scaledreading=0;

  //We use the min and max we find in the calibration sequence to automatically map the device
  //Scale the potentiometer, This particular one went from ~13 to ~ 830
  scaledreading= map(sensorValue, 
  sensorMin,sensorMax,  //Range of the sensor's output
  0, 255); //Range of the motor's output

  Serial.print("Scaled Value (0-255) ");
  Serial.print(scaledreading);     //Note, we should address the confusion of how to address inputs 1 and 2
  Serial.print(" | ");
  Serial.println();


  //Make the motor run with the specified value
  Toy.setOutput(0,scaledreading);

  Toy.setOutput(1,scaledreading);

  Toy.setOutput(2,scaledreading);
}



//Run the calibration sequence for the specified pin and specified amount of time
void calibration(int whichInput, long caltime){
    //Reset Min and Max for this calibration
    sensorMin = 1023;        // minimum sensor value
    sensorMax = 0;           // maximum sensor value
    
   //Signal beginning of Calibration
Toy.setLED(0,0);

  Toy.setOutput(-1,0);
long timer = millis();

  // calibrate during the first five seconds 
  while (millis() < timer+caltime) {

    
    sensorValue = Toy.getInput(whichInput);

    // record the maximum sensor value
    if (sensorValue > sensorMax) {
      sensorMax = sensorValue;
    }

    // record the minimum sensor value
    if (sensorValue < sensorMin) {
      sensorMin = sensorValue;
    }
         Serial.print("Timer ");
  Serial.print(timer+caltime);     //Note, we should address the confusion of how to address inputs 1 and 2
  Serial.print(" | ");

     Serial.print("Millis ");
  Serial.print(millis());     //Note, we should address the confusion of how to address inputs 1 and 2
  Serial.print(" | ");

    
        Serial.print("Min Value ");
  Serial.print(sensorMin);     //Note, we should address the confusion of how to address inputs 1 and 2
  Serial.print(" | ");

  Serial.print("Max Value ");
  Serial.print(sensorMax);     //Note, we should address the confusion of how to address inputs 1 and 2
  Serial.print(" | ");
  Serial.println();
delay(2);
  }

  // signal the end of the calibration period
   Toy.setLED(0,0);
  startupSequence();
  clicked = false;
  

}

void Click() {
  clicked = true;
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





