/* Snow Crash: TcDS


based mostly off blinkwithoutdelay:
 created 2005
 by David A. Mellis
 modified 8 Feb 2010
 by Paul Stoffregen
 
 This example code is in the public domain.
 */

// constants won't change. Used here to 
// set pin numbers:
const int ledPin =  11;      // the number of the LED pin

// Variables will change:
int ledState = LOW;             // ledState used to set the LED
long previousMillis = 0;        // will store last time LED was updated

// the follow variables is a long because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long interval =20;           // interval at which to blink (milliseconds)

void setup() {
  // set the digital pin as output:
  pinMode(ledPin, OUTPUT); 
  Serial.begin(9600);  
}

void loop()
{
  
   int sensorValue = analogRead(A0);
   Serial.println(sensorValue);

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
    digitalWrite(ledPin, ledState);
  }
}

