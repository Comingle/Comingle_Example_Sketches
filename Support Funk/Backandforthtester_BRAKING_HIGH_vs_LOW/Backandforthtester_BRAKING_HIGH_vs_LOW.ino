/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
 
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int gnd = 5;
int m1 = 6;

int m2=9;
int m3=10;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(gnd, OUTPUT);
    pinMode(m1, OUTPUT);
  pinMode(m2, OUTPUT);
    pinMode(m3, OUTPUT);
  digitalWrite(gnd, HIGH);   // turn the gndon (HIGH is the voltage level)
    digitalWrite(m1, LOW);   // turn the gndon (HIGH is the voltage level)
    digitalWrite(m2, LOW);   // turn the gndon (HIGH is the voltage level)
    digitalWrite(m3, LOW);   // turn the gndon (HIGH is the voltage level)

}

// the loop routine runs over and over again forever:
void loop() {
  
  //Just do on and off
  
  for (int i=0; i<8;i++){
  
  digitalWrite(gnd, HIGH);   // turn the gndon (HIGH is the voltage level)
     digitalWrite(m1, LOW);   // turn the gndon (HIGH is the voltage level)
    digitalWrite(m2, HIGH);   // turn the gndon (HIGH is the voltage level)
    digitalWrite(m3, HIGH);   // turn the gndon (HIGH is the voltage level)

  delay(200);               // wait for a second
  digitalWrite(gnd, LOW);    // turn the gndoff by making the voltage LOW
     digitalWrite(m1, LOW);   // turn the gndon (HIGH is the voltage level)
   // digitalWrite(m2, LOW);   // turn the gndon (HIGH is the voltage level)
   // digitalWrite(m3, LOW);   // turn the gndon (HIGH is the voltage level)
   delay(10);

  digitalWrite(gnd, HIGH);   // turn the gndon (HIGH is the voltage level)
     digitalWrite(m1, LOW);   // turn the gndon (HIGH is the voltage level)
    digitalWrite(m2, HIGH);   // turn the gndon (HIGH is the voltage level)
    digitalWrite(m3, HIGH);   // turn the gndon (HIGH is the voltage level)

  delay(200);               // wait for a second
  }
  
  //Then do reverse breaking
    for (int i=0; i<8;i++){
  
  digitalWrite(gnd, HIGH);   // turn the gndon (HIGH is the voltage level)
    digitalWrite(m1, LOW);   // turn the gndon (HIGH is the voltage level)
    digitalWrite(m2, HIGH);   // turn the gndon (HIGH is the voltage level)
    digitalWrite(m3, HIGH);   // turn the gndon (HIGH is the voltage level)

  delay(200);               // wait for a second
  
    digitalWrite(gnd, HIGH);    // turn the gndoff by making the voltage LOW
     digitalWrite(m1, HIGH);   // turn the gndon (HIGH is the voltage level)
    digitalWrite(m2, HIGH);   // turn the gndon (HIGH is the voltage level)
    digitalWrite(m3, HIGH);   // turn the gndon (HIGH is the voltage level)
   delay(10);

     digitalWrite(gnd, HIGH);    // turn the LED off by making the voltage LOW

    digitalWrite(m1, LOW);   // turn the gndon (HIGH is the voltage level)
    digitalWrite(m2, HIGH);   // turn the gndon (HIGH is the voltage level)
    digitalWrite(m3, HIGH);   // turn the gndon (HIGH is the voltage level)

  delay(200);               // wait for a second
  }
  
}
