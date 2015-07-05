#include "Wire.h"
//#include "WiiChuckClass.h" //most likely its WiiChuck.h for the rest of us.
#include "WiiChuck.h"

WiiChuck chuck = WiiChuck();


#include <OSSex.h>

int ledPin = 13;


void setup() {
  
      Toy.setID(BETA);  
  Toy.setHackerPort(HACKER_PORT_I2C); 
  
  //nunchuck_init();
  Serial.begin(9600);
  chuck.begin();
  chuck.update();
  //chuck.calibrateJoy();
      Serial.print("WiiChuckClassDemo ready\n");

}

void loop() {
  delay(20);
  chuck.update(); 
  


  Serial.print(chuck.readJoyX());
    Serial.print(", ");  
  Serial.print(chuck.readJoyY());
    Serial.print(", ");  

  if (chuck.buttonZ) {
     Serial.print("Z");
  } else  {
     Serial.print("-");
  }

    Serial.print(", ");  

//not a function//  if (chuck.buttonC()) {
  if (chuck.buttonC) {
    Toy.setOutput(-1,255);
     Serial.print("C");
  } else  {
     Serial.print("-");
  }

    Serial.print("   Accel Data ");  

    Serial.print(chuck.readRoll());
    Serial.print(", ");  
  Serial.print(chuck.readPitch());
    Serial.print(", ");  

    Serial.print((int)chuck.readAccelX()); 
    Serial.print(", ");  
    Serial.print((int)chuck.readAccelY()); 
    Serial.print(", ");  

    Serial.print((int)chuck.readAccelZ()); 
    Serial.print(", ");  
    Serial.println();

}
