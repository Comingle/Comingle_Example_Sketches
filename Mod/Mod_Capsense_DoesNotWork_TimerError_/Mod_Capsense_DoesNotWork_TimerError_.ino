/* The Mod Capacitive Touching Demo -- written by A Quitmeyer / Comingle. First released Dec 3, 2014 */
#include <CapacitiveSensor.h>

#include <OSSex.h>
bool clicked = false;
//CapacitiveSensor   cs_Sender_Sensor = CapacitiveSensor(Toy.device.inputs[1].pin,Toy.device.inputs[0].pin);
CapacitiveSensor   cs_Sender_Sensor = CapacitiveSensor(A3,A2); 
void setup() {
  // 0 for all Multivibes currently.
  Toy.setID(0);
  
  // Blip all the motors and flash the LED to show that everything is working and the device is on.
  //startupSequence();  
cs_Sender_Sensor.set_CS_Timeout_Millis(800);//timeout after 800 milliseconds = max touch

 Serial.begin(9600);
}

void loop() {
  
  long total3 =  cs_Sender_Sensor.capacitiveSensor(30);
   int val = map(total3,110,1000
   ,0,255);

    Serial.println(total3);                // print sensor output 3
    analogWrite(3,total3/100);	
    //Toy.setOutput(0, total3);
}


