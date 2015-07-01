/* Multivibe software -- written by Craig Durkin / Comingle. First released Aug 17, 2014 */
/* This software comes pre-loaded on Comingle Multivibe sex toys */

#include <OSSex.h>

bool clicked = false;
int baseline=0;



void setup() {
  // 0 for all Multivibes currently.
  Toy.setID(0);
  


  // Set up the button click handlers
  Toy.attachClick(click);

  //delay(1000);
  baseline = calibratesensor(Toy.device.inPins[0],300);
  
  Serial.begin(9600);
}



void loop() {
  int out0 = Toy.getInput(0);
  int out1 = Toy.getInput(1);

int val;
val = abs(out0- baseline);
  val=map(val,100,500,0,255); //Map Values
val=constrain(val,0,255);//constrain values

/**/
  Serial.print(out0);
  Serial.print(" | ");
    Serial.print(out1);
  Serial.print(" | ");
  Serial.println(val);
  /**/
  
Toy.setOutput(2, val);
//analogWrite(3,val);
Toy.setOutput(0,val-100);
Toy.setOutput(1,val/2);
 // delay(60);
}

float calibratesensor(int pin, int samples){
float base=0;
 for(int i =0; i<samples; i++){
  base= base+ analogRead(pin);
   
   delay(1);
 } 
  return base/samples;
  
  
}



void click() {
  clicked = true;
  calibratesensor(Toy.device.inPins[0],300);
  //Toy.cyclePattern();
}


