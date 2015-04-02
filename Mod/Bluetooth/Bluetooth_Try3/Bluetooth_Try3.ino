/*
 Bluetooth Board Example
 
 
 //Demo Mac Address:   
 6C:94:F8:DF:F2:75
 
 
 */
//#include <OSSex.h>

#include <Wire.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(15, 14); // RX (15 has to be RX), TX





int led = 13;

byte byteRead;
char myChar ; 

void setup()
{
  //Set in serial mode
    pinMode(8, OUTPUT);
    pinMode(12, OUTPUT);
    digitalWrite(8, LOW);
    digitalWrite(12, HIGH);
    
    //  Toy.setID(BETA);
//  Toy.setHackerPort(HACKER_PORT_SERIAL);
//  
pinMode(led,OUTPUT);
    

  

 
    Serial.begin(9600);
      while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
        Serial.println("Hey Serial");

      // set the data rate for the SoftwareSerial port
  mySerial.begin(115200); //default rate of bluetooth RN4020

    delay(1000);
    
    //Bluetooth Setup
    /*
    mySerial.println("+");
    delay(1000);
    mySerial.println("SF,1");
    delay(500);
    mySerial.println("SS,C0000000"); //Set device in peripheral mode and set turn on auto advertising
    delay(500);
    mySerial.println("SR,00000000");
    delay(500);
//    mySerial.println("S-,Dildoz");
//    delay(500);
    mySerial.println("R,1"); //Reboot
    delay(500);
    mySerial.println("LS"); //Start advertising
//    */
//This Code works well for just making it show up 
/**/ 

//NOTE: For some reason these changes don't take place UNTIL you open the serial monitor????
mySerial.println("SR,20000000"); //Set device in peripheral mode and set turn on auto advertising
   // mySerial.println("SF,1");
    delay(500);
    //mySerial.println("SS,C0000000"); 
    delay(500);
   // mySerial.println("SR,00000000");//Set device in peripheral mode and set turn on auto advertising
     mySerial.println("S-,DildoMO"); 
     //S-,DildoSenl
         delay(500);

    mySerial.println("R,1"); //Reboot
    delay(500);
    mySerial.println("A"); //Start advertising
    
   /**/
}

void loop()
{
  
  //Recieve
// while(mySerial.available()){
//    myChar = mySerial.read();
//    Serial.print(myChar);
//  }

//Send BLUEtooht from arduino

  while(Serial.available()){
   myChar = Serial.read();
   mySerial.print(myChar);
  }

//  digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
//  delay(100);              // wait for a second
//  digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
//  delay(100);              // wait for a second
}

