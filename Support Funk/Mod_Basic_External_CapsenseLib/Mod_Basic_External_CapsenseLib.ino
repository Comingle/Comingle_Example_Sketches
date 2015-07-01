#include <CapacitiveSensor.h>

/*
 * CapitiveSense Library Demo Sketch
 * Paul Badger 2008
 * Uses a high value resistor e.g. 10 megohm between send pin and receive pin
 * Resistor effects sensitivity, experiment with values, 50 kilohm - 50 megohm. Larger resistor values yield larger sensor values.
 * Receive pin is the sensor pin - try different amounts of foil/metal on this pin
 * Best results are obtained if sensor foil and wire is covered with an insulator such as paper or plastic sheet
 */

#include <OSSex.h>

CapacitiveSensor   cs_4_2 = CapacitiveSensor(A3,A2);        // 10 megohm resistor between pins A3 and A2, pin A2 is sensor pin, add wire, foil

void setup()                    
{
 Toy.setID(0);
//   cs_4_2.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example
cs_4_2.set_CS_Timeout_Millis(800);//timeout after 800 milliseconds = max touch

   Serial.begin(9600);
}

void loop()                    
{
    long start = millis();
    long total3 =  cs_4_2.capacitiveSensor(30);
 
    Serial.print(millis() - start);        // check on performance in milliseconds
    Serial.print("\t");                    // tab character for debug window spacing

    Serial.println(total3);                // print sensor output 3
//analogWrite(3,total3/100);
     Toy.setOutput(0, total3/100);

    delay(5);                             // arbitrary delay to limit data to serial port 
}
