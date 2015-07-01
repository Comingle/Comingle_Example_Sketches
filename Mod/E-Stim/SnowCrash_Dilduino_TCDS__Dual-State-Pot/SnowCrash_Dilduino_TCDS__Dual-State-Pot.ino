/* Snow Crash - Electronic Hallucinogen Dual Mode

Make blinking patterns in front of your eyes! Connect electrodes. Feel funky!

* {♥} COMINGLE --  2014/12/04 -- Share Freely

based mostly off blinkwithoutdelay:
 created 2005  by David A. Mellis
 This example code is in the public domain.
 */

// constants won't change. Used here to 
// set pin numbers:
const int zapPin =  6;      // This is the Analog input on HP0
const int inputPin = A2;   // This is the Analog input on top of Dilduino


// Variables will change:
int ledState = LOW;             // ledState used to set the LED
long previousMillis = 0;        // will store last time LED was updated

// the follow variables is a long because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long interval =120;           // interval at which to blink (milliseconds)

int brightness = 0;    // how bright the LED is
int fadeAmount = 5;    // how many points to fade the LED by






void setup() {
  
          //Set up the multiplexer to choose the correct style of inputs on hacker port
  pinMode(8, OUTPUT);
  pinMode(12, OUTPUT);
    digitalWrite(8, LOW);
  digitalWrite(12, LOW);
  
  pinMode(inputPin, INPUT);
  
  
  // set the digital pin as output:
  pinMode(zapPin, OUTPUT); 
  Serial.begin(9600);  
  
    pinMode(A3, OUTPUT); //Use extra voltage source from top of board
    digitalWrite(A3, HIGH);
       
       
  
}

void loop()
{
  
   int sensorValue = analogRead(inputPin); //Hooked up to potentiometer
   Serial.println(sensorValue);

//Split how the band functions at the halfway point

//From 0 - 512 the control will change the frequency of the pulsing
if(sensorValue<=512){
  interval = map(sensorValue, 0,512,0,180);
 unsigned long currentMillis = millis();
 
  if(currentMillis - previousMillis > interval) {
    // save the last time you blinked the LED 
    previousMillis = currentMillis;   

    // if the LED is off turn it on and vice-versa:
    if (ledState == LOW)
      ledState = HIGH;
    else
      ledState = LOW;

    // set the LED with the ledState of the variable:
    digitalWrite(zapPin, ledState);
  }
  
}

if(sensorValue>512){
    interval = map(sensorValue, 512,1023,10000,0);
  // set the brightness of zap pin:
  analogWrite(zapPin, brightness);   
  

  // change the brightness for next time through the loop:
  brightness = brightness + fadeAmount;
  // reverse the direction of the fading at the ends of the fade: 
  if (brightness == 0 || brightness == 255) {
    fadeAmount = -fadeAmount ; 
  } 
    
  // wait for 30 milliseconds to see the dimming effect    
  delayMicroseconds(interval);  
}


 
}

