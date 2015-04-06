#include <OSSex.h>

/* Hook up a a Joystick (made from two potentiometers) to Control
 * Example by Quitmyer/Comingle, Dec 9, 2014
 * {♥} COMINGLE --  2014/12/04 -- Share Freely
*/

void setup() {
  Toy.setID(0);

  Serial.begin(9600);
  
}

void loop() {
 
 int readingV= 0;
 readingV = Toy.getInput(0);
   int readingH= 0;
 readingH = Toy.getInput(1);
  
      Serial.print("Vertical ");
  Serial.print(readingV);     //Note, we should address the confusion of how to address inputs 1 and 2
  Serial.print(" | ");
        Serial.print("Horizontal ");
  Serial.print(readingH);     //Note, we should address the confusion of how to address inputs 1 and 2
  Serial.print(" | ");
  int scaledreadingV=0;
  
  //Scale the potentiometer, 
  scaledreadingV= map(readingV, 0,1024, 0, 255);
   int scaledreadingH=0;
  //Scale the potentiometer
  scaledreadingH= map(readingH, 0,1024, 0, 255);
  
      Serial.print("Scaled Value (0-255) ");
  Serial.print(scaledreadingV);     //Note, we should address the confusion of how to address inputs 1 and 2
  Serial.print(" | ");
     Serial.println();


  //Make the motor run with the specified value
    Toy.setOutput(0,scaledreadingH);

    

    Toy.setOutput(2,scaledreadingV);
}





