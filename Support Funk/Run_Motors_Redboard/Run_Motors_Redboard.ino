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
  pinMode(8, OUTPUT);
  digitalWrite(8, LOW);   
  
  pinMode(13, OUTPUT); 
  digitalWrite(13, HIGH);   
  
delay(500);

  pinMode(8, OUTPUT);
  digitalWrite(8, LOW);   
  
  pinMode(11, OUTPUT); 
  digitalWrite(11, HIGH);   

delay(500);

    pinMode(8, OUTPUT);
  digitalWrite(8, LOW);   
  
  pinMode(9, OUTPUT); 
  digitalWrite(9, HIGH);   

delay(500);
}

// the loop routine runs over and over again forever:
void loop() {
  pinMode(8, OUTPUT);
  digitalWrite(8, LOW);   
  
  pinMode(13, OUTPUT); 
  digitalWrite(13, HIGH);   
    digitalWrite(11, LOW);
   digitalWrite(9, LOW);   
   

delay(500);

  pinMode(8, OUTPUT);
  digitalWrite(8, LOW);   
  
  pinMode(11, OUTPUT); 
  digitalWrite(11, HIGH); 
  digitalWrite(13, LOW);   
  digitalWrite(9, LOW);   
  

delay(500);

    pinMode(8, OUTPUT);
  digitalWrite(8, LOW);   
  
  pinMode(9, OUTPUT); 
  digitalWrite(9, HIGH);  
   digitalWrite(13, LOW);   
  digitalWrite(11, LOW);   
 

delay(500);
}
