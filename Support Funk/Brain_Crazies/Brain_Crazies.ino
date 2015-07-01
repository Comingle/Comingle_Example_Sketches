/*
 Fade
 
 This example shows how to fade an LED on pin 9
 using the analogWrite() function.
 
 This example code is in the public domain.
 */

int led = 3;           // the pin that the LED is attached to
int brightness = 0;    // how bright the LED is
int fadeAmount = 1;    // how many points to fade the LED by

//microseconds
long BURST = 400000;


int varPulse = 5;
long lastPulse = 0;
long timeLapse = 10000;
boolean dir = false;
long high = 16;
long low = 0;



// the setup routine runs once when you press reset:
void setup()  { 
  // declare pin 9 to be an output:
  pinMode(led, OUTPUT);
  Serial.begin(28800);
  Serial1.begin(28800);
} 

// the loop routine runs over and over again forever:
void loop()  { 
  // set the brightness of pin 9:
  analogWrite(led, brightness);    

  // change the brightness for next time through the loop:
  brightness = brightness + fadeAmount;

  // reverse the direction of the fading at the ends of the fade: 
  if (brightness == 0 || brightness == 255) {
    fadeAmount = -fadeAmount ;
    if (brightness == 0){delayMicroseconds(BURST);}
    else{delayMicroseconds(BURST);}
  }     
    
  delayMicroseconds(varPulse);     

/*
  if (Serial1.available()){
    //varPulse = Serial.read(); 
    char input[5];
    Serial1.readBytesUntil('/n', input, 5);
    
    for (int i = 0; i < 5; i++){
      Serial.print(input[i]);
      Serial.print(",");
    }
    Serial.println();
    
  }
  
  Serial1.write('A');

  */

  /**/
  if (millis() - lastPulse > 200){
    if (varPulse >= high || varPulse <= low){dir = !dir;}  
    if (dir){varPulse++;}
    else{varPulse--;}
    lastPulse = millis();
    Serial.println(varPulse);
  }
/**/


}


/// 5Volts Pulse 40 Burst 400000
// 15volts pulse 4 burst 400000 creamy

