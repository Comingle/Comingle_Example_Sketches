/*
Bluetooth LTE 4.0 RN4020 to Dilduino (Arduino) Example
2015-04-06
{♥} COMINGLE -by A. Quitmeyer
Share alike please, but also just tossing into Public Domain

This example shows you how to get running with BT 4.0
and also how to go through all sorts of other tricky processes like

** Connecting with the RN 4020 Module
** Doing all this over Software Serial instead of hardware Serial
** Pairing with a peripheral (BT Heart Rate Monitor)
** Getting notifications of data from the peripheral

What's this BT?
It's that Weird fancy new BT that, only newer phones have (my comp don't have) and it operates with posting and sending services
more than just like a regular serial. There's some tricky stuff about it that's not too
well documented yet, so hopefully this helps out with that!
General documentation from Tom Igoe is here: https://github.com/tigoe/BLEDocs/wiki/Introduction-to-Bluetooth-LE


 */

//This example won't use any OSSEX
//#include <OSSex.h>

#include <SoftwareSerial.h>

//This is the software serial ports on the Dilduino (like Leonardo)
SoftwareSerial mySerial(15, 14); // RX (15 has to be RX), TX

int led = 13;

byte byteRead;
char myChar ;

void setup()
{
  //Set the Mux on the Dilduino in serial mode
  pinMode(8, OUTPUT);
  pinMode(12, OUTPUT);
  digitalWrite(8, LOW);
  digitalWrite(12, HIGH);

  //No OSSEX so none of these below
  //  Toy.setID(BETA);
  //  Toy.setHackerPort(HACKER_PORT_SERIAL);
  //

  //SETUP ALL THE SERIALS

  //Hardware Serial (UART)
  //We need this to be the same as the Soft Serial or else it doesn't work for me
  Serial.begin(2400);

  // set the data rate for the SoftwareSerial port
  mySerial.begin(2400); //default rate of bluetooth RN4020 is 115200, we changed it for more reliable data over Software serial

  //There's a good chance you might need to run the commands the first time by setting this to 115200 since that is default
  /*
  Initialize Bluetooth Baud to lower speed for Software Serial
    mySerial.begin(115200); //default rate of bluetooth RN4020 is 115200,
    delay(500);
    mySerial.println("SB,0"); // 0 = 2400 Baud   1 = 9600 baud  2= 19200 baud   4 = 115200 baud (default)
        delay(500);
      mySerial.println("R,1"); //Reboot
  delay(1000);

  */

  //Always nice to let it chill a bit
  delay(1000);

  //BLUETOOTH SETUP
  //Initialize BT RN4020
  


  //Set as central or as a peripheral device
  //mySerial.println("SR,20000000"); //Set device in peripheral mode and set turn on auto advertising
  mySerial.println("SR,92000000");// Set device as central, support MLDP and enable
  delay(500);

//Change the name that's displayed, this is always a good first thing to check in your debugging
  mySerial.println("S-,ComingleIZCool");
  delay(500);

//Reboot the sucker to make the changes stick. the light should turn off when you reboot (also good for debugging)
  mySerial.println("R,1"); //Reboot
  delay(1000);
  
  //Make the device show up on scanners
  mySerial.println("A"); //Start advertising
  delay(500);
  
  //List all the details about the Buetooth device (what it's connected to, it's Mac address, etc.
  mySerial.println("D"); //Get details of the RN4020 chip's current status

/*
//If all works out well, at this point you should have your device setup 
//for issuing and recieveing commands over the Serial Monitor
//To test if things are working
//type "D" and hit enter on the Serial Monitor

This gives a dump of all the details of the bluetooth chips status

  6C:94:F8:DF:F2:75  /Mac Address
  ComingleIZCool  //Name that you set
  Central // Role that you set
  Connected: no  //
  Bonded: no 
  Server Services: 80000000
  
 
 If you are getting something like that, good work, things seem to be communicating, let's try
 more advanced stuff next
 

*/

/*
-----------------------------
Connecting and getting information
-----------------------------



  How to connect to BT
  Type the command
  
        F 
  
  This starts scanning for nearby Bluetooth things
  it will list all their Mac addresses and stuff
  
When you see the correct device
use the "E" command to connect to it
My BT Heart Rate Monitor's device number was FE9693DDAB49
So i typed in this to connect

       E,1,FE9693DDAB49 // connect
       //*note if that doesn't work try E,0, FE9693DDAB49
       //This has to do with "Random" and "Public" address types
  
  
  Once connected
  You can look at all the different information your connected device can offer 
  by sending the command

        LC

This Lists the CLIENT SERVICES
You will get something that looks like this returned on the serial
  
  180D // This is all stuff with the Heart Rate monitor
    2A37,000B,00
    2A37,000C,02
    2A38,000E,10
    2A39,0010,08
  180F // This is all stuff with the battery
    2A19,0018,02
    2A19,0019,10
    
    
 This looks like a bunch of crazy garbage, but it's how Bluetooth 4.0 shares data
 data gets posted to little bulletin areas. and there are "Official" numbers that 
 designate certain types of data
 
"180F" for instance is the battery  state on the BT device
"180D" is the official designation for Heart Rate information (you can look these all up online)

The indented lines below are all the different messages available from that service. 

These messages have specific styles of reading information tied to each of them

If you want to READ DATA from a characteristic, it has to end in a "02"
For instance, we can look at the Battery status and see "0018" ends with "02" 
to read this on the RN4020
type

       CHR,0018

and you get back a message that says:
        
        R,64  //(which showss 100% battery life in Hexadecimal)


For more advanced information, like heart rate, you have to SUBSCRIBE to be NOTIFIED of the data
Data that will NOTIFY you ends in "10"

So to get the heart rate (BPM) from a nice cheap BT heart rate monitor 
(you can get clones of Polar's H7 for $15-25)
Do this

      CHW,000E,0100
      
      
  it then sends notify messages that look like this
      
      Notify,000E,0054

The last number there is Hexadecimal for your heart rate


Here's a rough example of doing something with that data
We can convert to human numbers


int BPM;
String str;
String valstring;

while (mySerial.available()) {
  
  str = mySerial.readStringUntil('\n');
  
  if(str.startsWith("Notify,000E"){ //make sure it is the one we are targetting
  
  valstring =  getStringPartByNr(str, ',', 2));  // the third part - 0054

BPM =  hexToDec(valstring);


  }

}





//Function to split by tokens
// from https://github.com/BenTommyE/Arduino_getStringPartByNr/blob/master/getStringPartByNr.ino
//
String getStringPartByNr(String data, char separator, int index)
{
    // spliting a string and return the part nr index
    // split by separator
    
    int stringData = 0;        //variable to count data part nr 
    String dataPart = "";      //variable to hole the return text
    
    for(int i = 0; i<data.length()-1; i++) {    //Walk through the text one letter at a time
      
      if(data[i]==separator) {
        //Count the number of times separator character appears in the text
        stringData++;
        
      }else if(stringData==index) {
        //get the text when separator is the rignt one
        dataPart.concat(data[i]);
        
      }else if(stringData>index) {
        //return text and stop if the next separator appears - to save CPU-time
        return dataPart;
        break;
        
      }

    }
    //return text if this is the last part
    return dataPart;
}


// Converting from Hex to Decimal:

// NOTE: This function can handle a positive hex value from 0 - 65,535 (a four digit hex string).
//       For larger/longer values, change "unsigned int" to "long" in both places.
// from https://github.com/benrugg/Arduino-Hex-Decimal-Conversion/blob/master/hex_dec.ino


unsigned int hexToDec(String hexString) {
  
  unsigned int decValue = 0;
  int nextInt;
  
  for (int i = 0; i < hexString.length(); i++) {
    
    nextInt = int(hexString.charAt(i));
    if (nextInt >= 48 && nextInt <= 57) nextInt = map(nextInt, 48, 57, 0, 9);
    if (nextInt >= 65 && nextInt <= 70) nextInt = map(nextInt, 65, 70, 10, 15);
    if (nextInt >= 97 && nextInt <= 102) nextInt = map(nextInt, 97, 102, 10, 15);
    nextInt = constrain(nextInt, 0, 15);
    
    decValue = (decValue * 16) + nextInt;
  }
  
  return decValue;
}




  */

  pinMode(led, OUTPUT);

}

void loop()
{
  
  
  //This code below will let everything on your arduino's Software Serial talk to the hardware serial
  //So you can see it all through
  while (mySerial.available()) {
    myChar = mySerial.read();
    Serial.print(myChar);
  }
  //  delay(500);              // wait for a second

  while (Serial.available()) {
    myChar = Serial.read();
    mySerial.print(myChar);
  }
}

