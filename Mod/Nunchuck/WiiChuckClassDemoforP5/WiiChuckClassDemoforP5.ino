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
  Serial.begin(115200);
  chuck.begin();
  chuck.update();
  //chuck.calibrateJoy();
      Serial.print("WiiChuckClassDemo ready\n");

}

void loop() {
   delay(20);
  chuck.update(); 


  Serial.print(chuck.readRoll());
    Serial.print(", ");  
  Serial.print(chuck.readPitch());
    Serial.print(", ");  

    Serial.print((int)chuck.readAccelX()); 
    Serial.print(", ");  
    Serial.print((int)chuck.readAccelY()); 
    Serial.print(", ");  

    Serial.print((int)chuck.readAccelZ()); 

    Serial.println();

}
