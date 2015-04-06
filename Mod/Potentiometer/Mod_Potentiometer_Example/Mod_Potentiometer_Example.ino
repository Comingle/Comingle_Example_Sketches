#include <OneButton.h>
#include <OSSex.h>

/* Hook up a Pot Knob to Control - this is like the easiest thing you can control it with
 * Example by Quitmyer/Comingle, Dec 4, 2014
 * {♥} COMINGLE --  2014/12/04 -- Share Freely
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
  scaledreading= map(reading, 
  110,760,  //Range of the sensor's output
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





