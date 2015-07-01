#include <OneButton.h>
#include <OSSex.h>

/* Rev up the MOD's power with a Stroke Sensor - Sensor adapted from Kobakant
* Example by Quitmyer/Comingle, Dec 5, 2014
 * {♥} COMINGLE --  2014/12/04 -- Share Freely
*/

int powervalue = 100;
int oldvalue = 0;
int diffThresh = 20;
void setup() {
  Toy.setID(0);

  Serial.begin(9600);
  
}

void loop() {
  int reading= 0;
 reading = Toy.getInput(0);
 
 int difference = abs(oldvalue-reading);

 
  Serial.print("reading ");
  Serial.print(reading);     
  Serial.print(" | ");
  
  Serial.print("difference ");
  Serial.print(difference);     
  Serial.print(" | ");
  
 
 
     Serial.println();

powervalue=difference;
  //Make the motor run with the specified value
    Toy.setOutput(0,powervalue);

        Toy.setOutput(1,powervalue);

    Toy.setOutput(2,powervalue);
    
    powervalue--;
    delay(100);
    oldvalue=reading;
}





