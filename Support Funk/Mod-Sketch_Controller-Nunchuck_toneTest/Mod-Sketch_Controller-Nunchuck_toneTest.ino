#include <Wire.h>
#include "WiiChuck.h"
WiiChuck nunchuck(c_update, z_update);

bool c_update() {
 return nunchuck.cPressed(); 
}
bool z_update() {
 return nunchuck.zPressed(); 
}

/* Mod Sketch v0.2 -- written by Craig Durkin / Comingle. */
/* This software comes pre-loaded on Comingle Mod sex toys */

/* Include the library */
#include <OSSex.h>

void setup() {
  // Set ID. ALPHA (0) or BETA (1) are current options.
  // The sketch won't compile until you set this!
  Toy.setID(BETA);
    Toy.setHackerPort(HACKER_PORT_I2C); 


  // Button will increase/decrease power by 20%
 // Toy.setPowerScale(0.2);
       Serial.print("WiiChuckClassDemo ready\n");

  
  // Blip all the motors and flash the LED to show that everything is working and the device is on.
  startupSequence();

  // Set the patterns that the button will cycle through. Toy will do nothing on startup, and clicking the button once will run the 'first' pattern
  // Clicking again will run 'second', etc.

  Toy.addPattern(rainforest);
  Toy.addPattern(sharpRamp);
  Toy.addPattern(sharpRampInv);
  Toy.addPattern(sharpRampControl);

  Toy.addPattern(fadeCos);
  Toy.addPattern(movemotor);
  Toy.addPattern(allRandom);

Toy.addPattern(weird3);
  Toy.addPattern(flicker);
  Toy.addPattern(weird2);
  Toy.addPattern(fadeOffset);
  Toy.addPattern(pulse2);


  Toy.addPattern(first);
  Toy.addPattern(second);
  Toy.addPattern(third);
  Toy.addPattern(pulse);
  

  // Set up the button click handlers
  Toy.attachClick(click);
  Toy.attachDoubleClick(doubleClick);
  Toy.attachLongPressStart(longPress);
  nunchuck.attachZClick( click);
  //  nunchuck.attachCClick( halt); //emergency, i just came shut down

 // nunchuck.attachCClick( blaster); //emergency, i just came shut down
  nunchuck.attachCClick( chargeblaster); //emergency, i just came shut down

  // Start the Serial console
  Serial.begin(9600);
  
   nunchuck.begin();
  nunchuck.update();

}

void halt(){
   Toy.stop(); 
}

void loop() {


serialProcessor();
nunchuckprintstats();

  tone(11, constrain(map(nunchuck.readRoll(),-70,70,40,2000),40,10000));


}

void nunchuckprintstats(){
   nunchuck.update(); 
Serial.print(nunchuck.readJoyX());
    Serial.print(", ");  
  Serial.print(nunchuck.readJoyY());
    Serial.print(", ");  

  if (z_update()) {
     Serial.print("Z");
  } else  {
     Serial.print("-");
  }

    Serial.print(", ");  

  if (c_update()) {
     Serial.print("C");
  } else  {
     Serial.print("-");
  }

    Serial.print("   Accel Data ");  

    Serial.print(nunchuck.readRoll());
    Serial.print(", ");  
  Serial.print(nunchuck.readPitch());
    Serial.print(", ");  

    Serial.print((int)nunchuck.readAccelX()); 
    Serial.print(", ");  
    Serial.print((int)nunchuck.readAccelY()); 
    Serial.print(", ");  

    Serial.print((int)nunchuck.readAccelZ()); 
    Serial.print(", ");  
    Serial.println();
  
}


void serialProcessor()
{
  // Serial console. Read a character in to command[1], and a value in to val
  char command[1];
  byte val;
if (Serial.available() > 0) {
    Serial.readBytes(command,1);
    if (command[0] == 'l') { // Set LED power
      val = Serial.parseInt();
      Toy.setLED(0,val);
      Serial.println(val);
    } else if (command[0] == '0' || command[0] == '1' || command[0] == '2') { // Set power of individual motor
      val = Serial.parseInt();
      Toy.setOutput(command[0], val);
      Serial.println(val);
    } else if (command[0] == '-') { // Catch '-1', set power of all motors
      int out = Serial.parseInt();
      out *= -1;
      val = Serial.parseInt();
      Toy.setOutput(out,val);
    } else if (command[0] == '{') {
      int motors[3];
      motors[0] = Serial.parseInt();
      motors[1] = Serial.parseInt();
      motors[2] = Serial.parseInt();
      for (int i = 0; i < 3; i++) {
        if (motors[i] >= 0) {
          Toy.setOutput(i, motors[i]);
        }
      }
    } else if (command[0] == 'p') {
      Serial.println(Toy.decreasePower());
    } else if (command[0] == 'P') {
      Serial.println(Toy.increasePower());
    } else if (command[0] == 't') { // Decrease pattern time, as in everything goes faster
      Serial.println(Toy.decreaseTime());
    } else if (command[0] == 'T') {
      Serial.println(Toy.increaseTime());
    } else if (command[0] == 'r') { // Run a specific pattern, r,0; r,1; etc.
      val = Serial.parseInt();
      Toy.runPattern(val);
      Serial.println(Toy.getPattern());
    } else if (command[0] == 'g') {  // Get number of currently running pattern
      Serial.println(Toy.getPattern());
    } else if (command[0] == 's') {
      Toy.stop();
    } else if (command[0] == 'c') {
      Toy.cyclePattern();
      Serial.println(Toy.getPattern());
    } else if (command[0] == 'i') { // Read input 0 or 1 and print it to serial port
      int in = Serial.parseInt();
      in %= Toy.device.inCount;
      Serial.println(Toy.getInput(in));
    }
  }
  
}

// Cycle through all the outputs, turn the LED on and leave it on to show that we're on
void startupSequence() {
  int outs = Toy.device.outCount;
  int outInterval = 100 / outs;

  Toy.setLED(0,128);

  for (int i = 0; i < outs; i++) {
    Toy.setOutput(i, 100+outInterval*i);
    delay(100);
    Toy.setOutput(i, 0);
    delay(50);
  }
  for (int i = 0; i < 3; i++) {
    Toy.setLED(0,0);
    delay(100);
    Toy.setLED(0,128);
    delay(100);
  }
}

// Click handler. Currently moves to next pattern.
void click() {
  Toy.cyclePattern();
}

// Double click handler Currently increases power.
void doubleClick() {
 Toy.increasePower();
}

// Click and hold handler. Currently decreases power.
void longPress() {
  Toy.decreasePower();
}

// Begin Pattern functions



//will return a scaling factor between 0 and 255 given a specific motor number, 
//and a number in a range of 0-1000
int virtualLoc(int val,int motornum){
float motorscale=-1;
  
  float berth = 500;
  //   float motor0pos = 0.0;
//  float motor1pos = 1000;
//  float motor2pos = 2000; //look below that equation does it
   float motorpos= motornum*berth;

  //total numbers right now is 1
  
//  takes a range between 0-1000

//current berth is 1 motor wide (so when all the way on one motor, others just stop
  
  val= map(val,0,1000,0,2000);
  
  
  motorscale = berth-abs(motorpos-val),0,1000; // calculate total distance
  motorscale = constrain(motorscale,0,1000);
  motorscale = map(motorscale,0,1000,0,255);
  return motorscale;
}

int movemotor(int seq) {
  
    Toy.step[0] = virtualLoc( nunchuck.readPitch(), 0);
  Toy.step[1] = virtualLoc( nunchuck.readPitch(), 1);
  Toy.step[2] = virtualLoc( nunchuck.readPitch(), 2);

//  Toy.step[0] = virtualLoc( nunchuck.readJoyY(), 0);
//  Toy.step[1] = virtualLoc( nunchuck.readJoyY(), 1);
//  Toy.step[2] = virtualLoc( nunchuck.readJoyY(), 2);
  Toy.step[3] = 50;
  return 1;
}

int first(int seq) {
  Toy.step[0] = 100;
  Toy.step[1] = 0;
  Toy.step[2] = 0;
  Toy.step[3] = 50;
  return 1;
}

int on_off(int seq) {
  if (seq % 20) {
    Toy.step[0] = 200;
  } else {
    Toy.step[0] = 0;
  }
  return 1;
}

// Second motor only
int second(int seq) {
  Toy.step[0] = 0;
  Toy.step[1] = 100;
  Toy.step[2] = 0;
  Toy.step[3] = 50;
  return 1;
}

// Third motor only
int third(int seq) {
  Toy.step[0] = 0;
  Toy.step[1] = 0;
  Toy.step[2] = 100;
  Toy.step[3] = 50;
  return 1;
}

// Turn on all outputs slightly offset from each other.
int flicker(int seq) {
  // set all motors initally to -1, ie "leave it alone"
  Toy.step[0] = Toy.step[1] = Toy.step[2] = -1;

  if (seq > 2) {
    Toy.step[3] = 200;
  } else {
    Toy.step[3] = 20;
  }

  seq %= 3;
  Toy.step[seq] = 80;

  return 1;
}


// Constant Randomly blip an output on for a short burst.
int pulse(int seq) {
  if (seq % 2) {
    Toy.step[0] = Toy.step[1] = Toy.step[2] = 0;
  } else {
    Toy.step[random(0,3)] = 144;
  }

  Toy.step[3] = 70;
  return 1;
}

int allRandom(int seq) {

Toy.step[0] = Toy.step[1] = Toy.step[2] = 0; 
  Toy.step[random(0,3)] = random(2)%2*100;
 
  Toy.step[3] = random(1,nunchuck.readJoyX());

return 1;

}

//Rain-like splattering
//When it's raining in the forest, all is right in the world - Peter Marting
int rainforest(int seq) {

Toy.step[0] = Toy.step[1] = Toy.step[2] = 0; //Reset all motors

  
  
Toy.step[random(0,3)] = constrain(map(nunchuck.readRoll(),-70,70,0,255),0,255); // drop a rainblob of standard impact strength
Toy.step[3] = random(10,20) ; // set standard time for a rainblob to hit


  
  return 1;
}





// Opposite of the first pulse() -- turn on all outputs, randomly blip one off
int pulse2(int seq) {
  if (seq % 2) {
    Toy.step[0] = Toy.step[1] = Toy.step[2] = 100;
  } else {
    Toy.step[random(0,3)] = 0;
  }

  Toy.step[3] = 100;

  
  
  return 1;
}


int weird2(int seq) {
  Toy.step[2] = round(127*cos(tan(tan(seq/(8*PI)))-PI/2)+127);
  Toy.step[3] = 30;
  return 1;
}

int weird3(int seq) {
  Toy.step[2] = round(50*(cos(seq/(8*PI)+PI/2) + sin(seq/2))+100);
  Toy.step[3] = 30;
  return 1;
}

int sharpRamp(int seq) {
  // neat exponential sequence inspired by github/jgeisler0303
  const uint8_t fadeTable[32] = {0, 1, 1, 2, 2, 2, 3, 3, 4, 5, 6, 7, 9, 10, 12, 15, 17, 21, 25, 30, 36, 43, 51, 61, 73, 87, 104, 125, 149, 178, 213, 255};

  seq %= 32;
  if (seq < 32) {
    
  
    Toy.step[0] = Toy.step[1] = Toy.step[2] = fadeTable[seq];
  }

    Toy.step[3] = constrain(map(nunchuck.readRoll(),-180,180,1,50),1,50);
return 1;
}

int sharpRampInv(int seq) { //cicada like
  // neat exponential sequence inspired by github/jgeisler0303
  const uint8_t fadeTable[32] = {0, 1, 1, 2, 2, 2, 3, 3, 4, 5, 6, 7, 9, 10, 12, 15, 17, 21, 25, 30, 36, 43, 51, 61, 73, 87, 104, 125, 149, 178, 213, 255};

  seq %= 32;
  if (seq < 32) {
    Toy.step[0] = Toy.step[1] = Toy.step[2] = (255-fadeTable[seq])*nunchuck.readJoyY()/255;
  }
  Toy.step[3] = 12;
     // Toy.step[3] = constrain(map(nunchuck.readJoyY(),0,255,9,15),1,200);

    Toy.step[3] = constrain(map(nunchuck.readRoll(),-70,70,1,100),1,100);
return 1;
}

void blaster() { //cicada like
  // neat exponential sequence inspired by github/jgeisler0303
  const uint8_t fadeTable[32] = {0, 1, 1, 2, 2, 2, 3, 3, 4, 5, 6, 7, 9, 10, 12, 15, 17, 21, 25, 30, 36, 43, 51, 61, 73, 87, 104, 125, 149, 178, 213, 255};

for (int i = 0; i<32; i++){
  Toy.setOutput(-1,fadeTable[i]);
  delay(constrain(map(nunchuck.readJoyY(),0,255,3,20),3,20));
}
    Toy.setOutput(-1,0);


}
void chargeblaster() { 
  // neat exponential sequence inspired by github/jgeisler0303
  const uint8_t fadeTable[32] = {0, 1, 1, 2, 2, 2, 3, 3, 4, 5, 6, 7, 9, 10, 12, 15, 17, 21, 25, 30, 36, 43, 51, 61, 73, 87, 104, 125, 149, 178, 213, 255};

for (int i = 0; i<32; i++){
  Toy.setOutput(0, fadeTable[i]);
  Toy.setOutput(1,fadeTable[constrain(i+4,0,31)]);
    Toy.setOutput(2,fadeTable[constrain(i+8,0,31)]);

  delay(constrain(map(nunchuck.readJoyY(),0,255,3,20),3,20));
}
    Toy.setOutput(-1,0);


}


int sharpRampControl(int seq) { //cicada like
  // neat exponential sequence inspired by github/jgeisler0303
  const uint8_t fadeTable[32] = {0, 1, 1, 2, 2, 2, 3, 3, 4, 5, 6, 7, 9, 10, 12, 15, 17, 21, 25, 30, 36, 43, 51, 61, 73, 87, 104, 125, 149, 178, 213, 255};

  seq %= 32;
  if (seq < 32) {
         Toy.step[0] = constrain(virtualLoc( nunchuck.readJoyY(), 0)-fadeTable[seq],0,255);
  Toy.step[1] = constrain(virtualLoc( nunchuck.readJoyY(), 1)-fadeTable[seq],0,255);
  Toy.step[2] = constrain(virtualLoc( nunchuck.readJoyY(), 2)-fadeTable[seq],0,255);
    
    //Toy.step[0] = Toy.step[1] = Toy.step[2] = constrain(nunchuck.readJoyY()-fadeTable[seq],0,255);
  }
  Toy.step[3] = 12;
    Toy.step[3] = constrain(map(nunchuck.readRoll(),-70,70,1,100),1,100);

   // Toy.step[3] = constrain(map(nunchuck.readPitch(),40,140,1,60),1,60);
return 1;
}

int fadeCos(int seq) {
  Toy.step[0] = Toy.step[1] = Toy.step[2] = round(127 * cos((seq / (PI*constrain(map(nunchuck.readJoyY(),0,255,1,15),1,15)))-PI) + 127);
       // Toy.step[3] = constrain(map(nunchuck.readJoyY(),0,255,9,15),1,200);
  Toy.step[3] = 50;
  return 1;
}

int fadeOffset(int seq) {
  // cos sequence takes 158 steps to run. start motor 1 a third of the way in (53 steps), start motor 2 2/3 (106 steps) of the way in.
  Toy.step[0] = round(127 * cos((seq / (8*PI))-PI) + 127);
  if (seq >= 58) {
    Toy.step[1] = round(127 * cos(((seq-58) / (8*PI))-PI) + 127);
  }
  if (seq >= 106) {
    Toy.step[2] = round(127 * cos(((seq-106) / (8*PI))-PI) + 127);
  }
  Toy.step[3] = 50;
  return 1;
}

// note: the _in array should have increasing values
int multiMap(int val, int* _in, int* _out, uint8_t size)
{
  // take care the value is within range
  // val = constrain(val, _in[0], _in[size-1]);
  if (val <= _in[0]) return _out[0];
  if (val >= _in[size-1]) return _out[size-1];

  // search right interval
  uint8_t pos = 1;  // _in[0] allready tested
  while(val > _in[pos]) pos++;

  // this will handle all exact "points" in the _in array
  if (val == _in[pos]) return _out[pos];

  // interpolate in the right segment for the rest
  return (val - _in[pos-1]) * (_out[pos] - _out[pos-1]) / (_in[pos] - _in[pos-1]) + _out[pos-1];
}
