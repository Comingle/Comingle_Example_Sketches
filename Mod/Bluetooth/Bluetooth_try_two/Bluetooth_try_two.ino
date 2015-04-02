/*
 * WiiChuckDemo -- 
 Hacked for COMINGLE
 *
 * 2008 Tod E. Kurt, http://thingm.com/
 *
 */
#include <OSSex.h>

#include <Wire.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(15, 17); // RX (15 has to be RX), TX
//


int ledPin = 13;

byte byteRead;
char myChar ; 

void setup()
{


    
  Toy.setID(BETA);
  Toy.setHackerPort(HACKER_PORT_SERIAL);
  
  

 
    Serial.begin(115200);
      while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
        Serial.println("Hey Serial");

      // set the data rate for the SoftwareSerial port
  mySerial.begin(115200); //default rate of bluetooth RN4020
      mySerial.println("Hey Software");

    delay(1000);
    
    //Bluetooth Setup
    
//    Serial.println("+");
//    delay(1000);
//    Serial.println("SF,1");
//    delay(500);
//    Serial.println("SS,C0000000"); //Set device in peripheral mode and set turn on auto advertising
//    delay(500);
//    Serial.println("SR,00000000");
//    delay(500);
//    Serial.println("R,1"); //Reboot
//    delay(5000);
//    Serial.println("LS"); //Start advertising
////    
    mySerial.println("SR,20000000"); //Set device in peripheral mode and set turn on auto advertising
    mySerial.println("R,1"); //Reboot
    delay(500);
    mySerial.println("A"); //Start advertising
}

void loop()
{
 while(mySerial.available()){
    myChar = mySerial.read();
    Serial.print(myChar);
  }

  while(Serial.available()){
   myChar = Serial.read();
   mySerial.print(myChar);
  }

  digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(100);              // wait for a second
  digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
  delay(100);              // wait for a second
}

