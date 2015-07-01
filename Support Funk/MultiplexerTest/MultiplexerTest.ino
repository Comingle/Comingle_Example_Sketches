/*
Multiplexer Test
 */
 
int pinS1 = 12;
int pinS0 = 8;
int sensorPin = A0;    // select the input pin for the potentiometer
int sensorValue = 0;  // variable to store the value coming from the sensor

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
    pinMode(13, OUTPUT);     

  pinMode(pinS1, OUTPUT);     
    pinMode(pinS0, OUTPUT);     

}

// the loop routine runs over and over again forever:
void loop() {
  

  digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
    digitalWrite(pinS1, HIGH);   // turn the LED on (HIGH is the voltage level)
    digitalWrite(pinS0, HIGH);   // turn the LED on (HIGH is the voltage level)
  sensorValue = analogRead(sensorPin);    
  Serial.print("sensor HIGHHIGH = " );                       
  Serial.println(sensorValue);  
  delay(1000);               // wait for a second
  digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
     digitalWrite(pinS1pinS0, LOW);   // turn the LED on (HIGH is the voltage level)
    digitalWrite(pinS0pinS1, HIGH);   // turn the LED on (HIGH is the voltage level)
  
  Serial.print("sensor LOWHIGH = " );                       
  Serial.println(sensorValue);  

  delay(1000);               // wait for a second
}
