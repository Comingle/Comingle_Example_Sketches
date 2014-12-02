#include <OneButton.h>
#include <OSSex.h>

/* Hook up a Pot Knob to Control
 * Example by Quitmyer/Comingle, Dec 9, 2014
 * {♥} COMINGLE
*/

void setup() {
  Toy.setID(0);

  Serial.begin(9600);
  
}

void loop() {
 
 int reading= 0;
 reading = Toy.getInput(0);
  
      Serial.print("potentiometer Value ");
  Serial.print(reading);     //Note, we should address the confusion of how to address inputs 1 and 2
  Serial.print(" | ");
  
  int scaledreading=0;
  //Scale the potentiometer, This particular one went from ~13 to ~ 830
  scaledreading= map(reading, 13,830, 0, 255);
  
      Serial.print("Scaled Value (0-255) ");
  Serial.print(scaledreading);     //Note, we should address the confusion of how to address inputs 1 and 2
  Serial.print(" | ");
     Serial.println();


  //Make the motor run with the specified value
    Toy.setOutput(0,scaledreading);

        Toy.setOutput(1,scaledreading);

    Toy.setOutput(2,scaledreading);
}





