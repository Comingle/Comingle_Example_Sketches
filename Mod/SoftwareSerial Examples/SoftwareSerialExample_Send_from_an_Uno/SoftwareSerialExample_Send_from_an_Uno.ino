/*
*/

#include <SoftwareSerial.h>

SoftwareSerial mySerial(9,11); 
void setup()
{
;
  
  // Open serial communications and wait for port to open:
  Serial.begin(57600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }


  Serial.println("Uno moon!");

  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
  mySerial.println("Hello, world?");
}

void loop() // run over and over
{
  
      mySerial.println("Uno Testt?");
//delay(30);

//  if (mySerial.available())
//    Serial.write(mySerial.read());
//  if (Serial.available())
//    mySerial.write(Serial.read());
}

