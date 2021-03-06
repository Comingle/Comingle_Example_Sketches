#include <AltSoftSerial.h>
//#include <OSSex.h>


// AltSoftSerial always uses these pins:
//
// Board          Transmit  Receive   PWM Unusable
// -----          --------  -------   ------------
// Teensy 3.0 & 3.1  21        20         22
// Teensy 2.0         9        10       (none)
// Teensy++ 2.0      25         4       26, 27
// Arduino Uno        9         8         10
// Arduino Leonardo   5        13       (none)
// Arduino Mega      46        48       44, 45
// Wiring-S           5         6          4
// Sanguino          13        14         12

//COMINGLE CHANGED // Arduino Leonardo   5        13       (none)
// to this                               14 tx     15rx

AltSoftSerial altSerial;

int led = 13;
  char c;


void setup() {
  
  
  pinMode(led,OUTPUT);
    
      //Set in serial mode
    pinMode(8, OUTPUT);
    pinMode(12, OUTPUT);
    digitalWrite(8, LOW);
    digitalWrite(12, HIGH);
//  Toy.setID(BETA);
//  Toy.setHackerPort(HACKER_PORT_SERIAL);
//  
  
  
  Serial.begin(9600);
  while (!Serial) ; // wait for Arduino Serial Monitor to open
  Serial.println("AltSoftSerial Test Begin");
  altSerial.begin(115200);
  altSerial.println("Hello World");
  
  
      altSerial.println("+");
    delay(1000);
    altSerial.println("SF,1");
    delay(500);
    altSerial.println("SS,C0000000"); //Set device in peripheral mode and set turn on auto advertising
    delay(500);
    altSerial.println("SR,00000000");
    delay(500);
     altSerial.println("S-,Dildoz");
    delay(500);
    altSerial.println("R,1"); //Reboot
    delay(5000);
    altSerial.println("LS"); //Start advertising
  
}

void loop() {

  if (Serial.available()) {
    c = Serial.read();
    altSerial.print(c);
  }
//  if (altSerial.available()) {
//    c = altSerial.read();
//    Serial.print(c);
//  }
}

