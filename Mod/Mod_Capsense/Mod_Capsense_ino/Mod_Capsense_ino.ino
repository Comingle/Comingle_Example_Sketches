#include <CapacitiveSensor.h>

/* The Mod Capacitive Touching Demo -- written by A Quitmeyer / Comingle. First released Dec 3, 2014 */
//Adapted from Badger

#include <OSSex.h>

CapacitiveSensor   cs_Sender_Sensor = CapacitiveSensor(A3,A2);        // 10 megohm resistor between pins A3 and A2, pin A2 is sensor pin, add wire, foil

void setup()                    
{
cs_Sender_Sensor.set_CS_Timeout_Millis(800);//timeout after 800 milliseconds = max touch

   Serial.begin(9600);
}

void loop()                    
{
    long start = millis();
    long total =  cs_Sender_Sensor.capacitiveSensor(30);
 if(total ==-2){
   analogWrite(3,255);// -2 means the sensor is maxed out
 }
 else{
    Serial.print(millis() - start);        // check on performance in milliseconds
    Serial.print("\t");                    // tab character for debug window spacing


    Serial.println(total);                // print sensor output 3

//Note you need to use different mappings with differnt attachments

total = map(total, 900,10000,0,255); //When plugged into a computer that is also connected to the wall
//total = map(total, 900,10000,0,255); //When plugged into a computer just running on battery

 total = constrain(total, 0, 255); //the mapping function will give negative values
analogWrite(3,total); //WHen doing capacitive sensing, we need to address the motors specifically
                          //For the current mod motor 0 = 3  m2 = 9 and m3 = 
    // CANNOT DO: Toy.setOutput(0, total3/100); //Note that we cannot use the library's methods because of a timer conflict
 }
    delay(5);                             // arbitrary delay to limit data to serial port 
}
