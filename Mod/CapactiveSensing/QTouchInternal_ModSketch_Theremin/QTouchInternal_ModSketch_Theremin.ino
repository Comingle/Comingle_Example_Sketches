/* Mod Sketch v0.2 -- written by Craig Durkin / Comingle. */
/* This software comes pre-loaded on Comingle Mod sex toys */

/* Include the library */
#include <OSSex.h>
#include <ADCTouch.h>

int ref0, ref1;       //reference values to remove offset

int led = 13;

 int qvalue0;
int     qvalue1;

#include <Wire.h>




void setup() {
  
  //QTOUCH setup
   // No pins to setup, pins can still be used regularly, although it will affect readings

   // Serial.begin(9600);

    ref0 = ADCTouch.read(A2, 500);    //create reference values to 
    ref1 = ADCTouch.read(A3, 500);      //account for the capacitance of the pad
pinMode(led,OUTPUT);

////////////
  
  // Set ID. ALPHA (0) or BETA (1) are current options.
  // The sketch won't compile until you set this!
  Toy.setID(BETA);

  // Button will increase/decrease power by 20%
 // Toy.setPowerScale(0.2);
  
  // Blip all the motors and flash the LED to show that everything is working and the device is on.
  startupSequence();

  // Set the patterns that the button will cycle through. Toy will do nothing on startup, and clicking the button once will run the 'first' pattern
  // Clicking again will run 'second', etc.

  Toy.addPattern(andyRain);

  Toy.addPattern(first);
  Toy.addPattern(second);
  Toy.addPattern(third);
  Toy.addPattern(pulse);
  Toy.addPattern(fadeCos);
  Toy.addPattern(weird3);
  Toy.addPattern(sharpRamp);
  Toy.addPattern(flicker);
  Toy.addPattern(weird2);
  Toy.addPattern(fadeOffset);
  Toy.addPattern(pulse2);

  // Set up the button click handlers
  Toy.attachClick(click);
  Toy.attachDoubleClick(doubleClick);
  Toy.attachLongPressStart(longPress);

  // Start the Serial console
  Serial.begin(9600);

}



void loop() {
  

  
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
  
   qvalue0 = ADCTouch.read(A2);   //no second parameter
     qvalue1 = ADCTouch.read(A3);     //   --> 100 samples

    qvalue0 -= ref0;       //remove offset
    qvalue1 -= ref1;

    Serial.print(qvalue0 > 40);    //return pressed or not pressed
    Serial.print("\t");
    Serial.print(qvalue1 > 40);
    Serial.print("\t\t");
    Serial.print(qvalue0);             //return value
    Serial.print("\t");
    Serial.println(qvalue1);
    analogWrite(led,constrain(qvalue0*3,0,255));
    
    Toy.setOutput(-1,constrain(qvalue0*3,0,255));
    
    delay(100);

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

// First motor only
// Why have a 50ms timing on the step (Toy.step[3]) ? This lets you adjust the power of the pattern,
// so that instead of running [100, 0, 0, 50] the whole time, it might become [120, 0, 0, 50] after a button click
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

int andyRandomBlip(int seq) {

Toy.step[0] = Toy.step[1] = Toy.step[2] = 0; 
  Toy.step[random(0,3)] = random(2)%2*100;
 
  Toy.step[3] = random(20,150);

return 1;

}

// Andy Test Rain
int andyRain(int seq) {

Toy.step[0] = Toy.step[1] = Toy.step[2] = 0; //Reset all motors

//Decide if to drop a raindrop or not

if(!random(
4
)
  
  ){ // Every now and then will return a 0, which we add a ! to to make the statement true
Toy.step[random(0,3)] = 100; // drop a rainblob of standard impact strength
Toy.step[3] = 20; // set standard time for a rainblob to hit
}
else{
 
  Toy.step[3] = random(1,150); //random amount of time between drops
}
  
  return 1;
}



// Raindrops auto-cycling a storm
int andyRainCycle(int seq) {

Toy.step[0] = Toy.step[1] = Toy.step[2] = 0; //Reset all motors

//Decide if to drop a raindrop or not

if(!random(
  
  round(5 * cos((seq / (100*PI)))-PI))
  
  ){ // Every now and then will return a 0, which we add a ! to to make the statement true
Toy.step[random(0,3)] = 100; // drop a rainblob of standard impact strength
Toy.step[3] = 60; // set standard time for a rainblob to hit
}
else{
 
  Toy.step[3] = random(20,150); //random amount of time between drops
}
  
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
  Toy.step[3] = 12;
}

int fadeCos(int seq) {
  Toy.step[0] = Toy.step[1] = Toy.step[2] = round(127 * cos((seq / (8*PI))-PI) + 127);
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
