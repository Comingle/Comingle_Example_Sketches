/*
 This runs the blink command for all the output ports
 {♥} COMINGLE
   This example code is in the public domain.
 */
 
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led = 13;


// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);   
  pinMode(11, OUTPUT);     
    pinMode(10, OUTPUT);     

  pinMode(9, OUTPUT);     
  pinMode(3, OUTPUT);     

  
}

// the loop routine runs over and over again forever:
void loop() {
    digitalWrite(3, HIGH);   // turn the LED on (HIGH is the voltage level)

  delay(500);               // wait for a second
  digitalWrite(3, LOW);    // turn the LED off by making the voltage LOW
    digitalWrite(9, HIGH);   // turn the LED on (HIGH is the voltage level)

  delay(500);               // wait for a second
    digitalWrite(9, LOW);    // turn the LED off by making the voltage LOW
    digitalWrite(10, HIGH);   // turn the LED on (HIGH is the voltage level)

  delay(500);               // wait for a second
    digitalWrite(10, LOW);    // turn the LED off by making the voltage LOW
    digitalWrite(11, HIGH);   // turn the LED on (HIGH is the voltage level)

  delay(500);               // wait for a second
  
  digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
   digitalWrite(11, LOW);   // turn the LED on (HIGH is the voltage level)

  delay(500);               // wait for a second
  digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW

  delay(800);               // wait for a second
}
