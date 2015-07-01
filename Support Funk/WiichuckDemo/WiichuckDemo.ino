/*
 * WiiChuckDemo -- 
 Hacked for COMINGLE
 *
 * 2008 Tod E. Kurt, http://thingm.com/
 *
 */
#include <OSSex.h>

#include <Wire.h>
#include "nunchuck_funcs.h"



int loop_cnt=0;

byte accx,accy,zbut,cbut;
int ledPin = 13;


void setup()
{
    Toy.setID(BETA);  
  Toy.setHackerPort(HACKER_PORT_I2C); 
   pinMode(8, OUTPUT);
    pinMode(12, OUTPUT);
    digitalWrite(8, HIGH);
    digitalWrite(12, LOW);
  
    Serial.begin(19200);
   // nunchuck_setpowerpins();
    nunchuck_init(); // send the initilization handshake
    
    Serial.print("WiiChuckDemo ready\n");
}

void loop()
{
 
 //For testing that our i2c inputs actually works 
//  pinMode(2,OUTPUT);
//  digitalWrite(2,HIGH);
//    pinMode(3,OUTPUT);
//  digitalWrite(3,LOW);
  
    if( loop_cnt > 100 ) { // every 100 msecs get new data
        loop_cnt = 0;

        nunchuck_get_data();
        
       /*

        accx  = nunchuck_accelx(); // ranges from approx 70 - 182
        accy  = nunchuck_accely(); // ranges from approx 65 - 173
            //    accz  = nunchuck_accelz(); // ranges from approx 65 - 173

        zbut = nunchuck_zbutton();
        cbut = nunchuck_cbutton(); 
            
        Serial.print("accx: "); Serial.print((byte)accx,DEC);
        Serial.print("\taccy: "); Serial.print((byte)accy,DEC);
        Serial.print("\tzbut: "); Serial.print((byte)zbut,DEC);
        Serial.print("\tcbut: "); Serial.println((byte)cbut,DEC);
        /*/
        nunchuck_print_data();
        
    }
    loop_cnt++;
    delay(1);
    
    
}

