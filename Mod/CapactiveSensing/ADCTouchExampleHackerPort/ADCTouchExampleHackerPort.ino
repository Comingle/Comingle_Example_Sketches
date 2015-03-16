/* QTouch Sensing

Using QTouch Capacitive Touch Sensing for more reliable touch sensing without grounding
* {♥} COMINGLE --  2015/03/11 -- Share Freely


 */
 
 
#include <ADCTouch.h>

int ref0, ref1;       //reference values to remove offset
int led = 13;

// variables:
int sensorValue = 0;         // the sensor value
int sensorMin = 9999;        // minimum sensor value
int sensorMax = -9999;           // maximum sensor value

int sensePinA= A3;
int sensePinB= A9;

void setup() 
{
  
    Serial.begin(9600);
          //Set up the multiplexer to choose the correct style of inputs on hacker port
  pinMode(8, OUTPUT);
  pinMode(12, OUTPUT);
    digitalWrite(8, LOW);
  digitalWrite(12, LOW);
  

pinMode(led, OUTPUT);
    ref0 = ADCTouch.read(sensePinA, 500);    //create reference values to 
    ref1 = ADCTouch.read(sensePinB, 500);      //account for the capacitance of the pad


 // turn on LED to signal the start of the calibration period:
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
   digitalWrite(13, LOW);
  delay(100);
  digitalWrite(13, HIGH);
    delay(100);
     digitalWrite(13, LOW);
  delay(100);
    pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
     delay(100);
     digitalWrite(13, LOW);

  // calibrate during the first four seconds 
  while (millis() < 4000) {
         sensorValue = ADCTouch.read(sensePinA);   
         sensorValue -= ref0;


    // record the maximum sensor value
    if (sensorValue > sensorMax) {
      sensorMax = sensorValue;
    }

    // record the minimum sensor value
    if (sensorValue < sensorMin) {
      sensorMin = sensorValue;
    }
  }

  // signal the end of the calibration period
  digitalWrite(13, LOW);
  delay(100);
  digitalWrite(13, HIGH);
    delay(100);
     digitalWrite(13, LOW);
  delay(100);
    pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
     delay(100);
     digitalWrite(13, LOW);

} 

void loop() 
{
    int value0 = ADCTouch.read(sensePinA);   //no second parameter
    int value1 = ADCTouch.read(sensePinB);     //   --> 100 samples

    value0 -= ref0;       //remove offset
    value1 -= ref1;

    Serial.print(value0 > 40);    //return pressed or not pressed
    Serial.print("\t");
    Serial.print(value1 > 40);
    Serial.print("\t\t");
     value0=constrain(map(value0,sensorMin,sensorMax,0,255),0,255);
    Serial.print(value0);             //return value
    Serial.print("\t");
    Serial.println(value1);
    
    
    analogWrite(led,value0
   );
   
   
    delay(100);
}
