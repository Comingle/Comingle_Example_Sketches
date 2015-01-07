/* Tonga base software -- written by Craig Durkin / Comingle. First released Aug 17, 2014 */
/* This software comes pre-loaded on Tonga sex toys */

#include <OSSex.h>

void setup() {
  // 0 for all Multivibes currently.
  Toy.setID(0);
  
  // Button will increase/decrease power by 20%
  Toy.setScale(0.2);
  
  // Blip all the motors and flash the LED to show that everything is working and the device is on.
  startupSequence();

  // Set the patterns that the button will cycle through
  Toy.addPattern(first);
  Toy.addPattern(second);
  Toy.addPattern(third);
  Toy.addPattern(pulse);
  Toy.addPattern(fadeCos);
  Toy.addPattern(weird3);
  Toy.addPattern(flicker);
  Toy.addPattern(weird2);
  Toy.addPattern(fadeSequence);
  Toy.addPattern(fadeOffset);
  Toy.addPattern(pulse2);

  // Set up the button click handlers
  Toy.attachClick(click);
  Toy.attachDoubleClick(doubleClick);
  Toy.attachLongPressStart(longPress);
  
Serial.begin(9600);
Serial.println("Setup");

}

// There are 3 motors total.
// You select them by setting 0, 1, or 2.
// Then you set the power from 0 to 255.
void loop() {
  startupSequence();
delay(2000);
Serial.println("OK");

  
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

void click() {
  Toy.cyclePattern();
}

void doubleClick() {
  Toy.increasePower();
}

void longPress() {
  Toy.decreasePower();
}

// Begin Pattern functions

int step[3];
int* blip(int seq) {
  step[0] = -1;
  
  seq %= 5;

  if (seq % 2) {
    step[1] = 0;
  } else {
    step[1] = 200;
  }

  step[2] = 1000;

  if (seq == 4) {
    return NULL;
  } else {
    return step;
  }
}

// Turn on all outputs slightly offset from each other. Continues to generate steps even after outputs are on so that the power can be adjusted.
int* flicker(int seq) {
  if (seq > 2) {
    step[2] = 200;
  } else {
    step[2] = 20;
  }
  seq %= 3;
  step[0] = seq;
  step[1] = 80;
 
  return step;
}

// Randomly blip an output on for a short burst.
int* pulse(int seq) {
  if (seq % 2) {
    step[0] = -1;
    step[1] = 0;
  } else {
    step[0] = random(0,3);
    step[1] = 144;
  }
  step[2] = 70;
  return step;
}

// Opposite of pulse() -- turn on all outputs, randomly blip one off
int* pulse2(int seq) {
  if (seq % 2) {
    step[0] = -1;
    step[1] = 100;
  } else {
    step[0] = random(0,3);
    step[1] = 0;
  }
  step[2] = 100;
  return step;
}

// fade output 0 in and out, fade output 1 in as 0 is fading out, fade output 2 in as 1 as fading out.
int* fadeOffset(int seq) {
  step[2] = 60;

  // sequence runs: 0 -> 255 -> 0 in 5 step increments.
  // 0 -> 255: 51 steps.
  // 255 -> 0: 51 steps;
  // -> 102 steps per output, 306 steps total.
  // normalize sequence
  seq %= 306;
  
  // output 0
  if (seq < 51) {
    step[0] = 0;
    step[1] = fadeNormalize(seq);
    // output 0 and 1
  } else if (seq < 154) {
    if (seq % 2) {
      step[0] = 1;
      step[1] = 2.5*(seq-51);
      step[2] = 30;
    } else {
      step[0] = 0;
      step[1] = 255 - 2.5*(seq-52);
      step[2] = 30;
    }
    // outputs 1 and 2
  } else if (seq < 256) {
    if (seq % 2) {
      step[0] = 2;
      step[1] = 2.5*(seq-153);
      step[2] = 30;
    } else {
      step[0] = 1;
      step[1] = 255 - 2.5*(seq-154);
      step[2] = 30;
    }
    // output 2
  } else {
    step[0] = 2;
    step[1] = fadeNormalize(seq);
  }
  return step;
}

int* first(int seq) {
  step[0] = 0;
  step[1] = 100;
  step[2] = 200;
  return step;
}

int* second(int seq) {
  step[0] = 1;
  step[1] = 100;
  step[2] = 200;
  return step;
}

int* third(int seq) {
  step[0] = 2;
  step[1] = 100;
  step[2] = 200;
  return step;
}

int* weird2(int seq) {
  step[0] = 0;
  step[2] = 30;
  step[1] = round(127*cos(tan(tan(seq/(8*PI)))-PI/2)+127);
  return step;
}

int* weird3(int seq) {
  step[0] = 2;
  step[2] = 30;
  step[1] = round(50*(cos(seq/(8*PI)+PI/2) + sin(seq/2))+100);
  return step;
}

int *fadeCos(int seq) {
  step[0] = -1;
  step[2] = 50;
  step[1] = round(127 * cos((seq / (8*PI))-PI) + 127);
  return step;
}

int* fadeSequence(int seq) {
  step[2] = 30;

  // sequence runs: 0 -> 255 -> 0 in 5 step increments.
  // 0 -> 255: 51 steps.
  // 255 -> 0: 51 steps;
  // -> 102 steps per output, 306 steps total.
  // normalize sequence
  seq %= 306;
  
  if (seq < 103) {
    step[0] = 0;
  } else if (seq < 205) {
    step[0] = 1;
  } else {
    step[0] = 2;
  }
  
  step[1] = fadeNormalize(seq);
  return step;
}

// outputs the proper power level for our fade sequence. we know that it's 102 steps to go from 0 to 255 back to 0 in 5 step increments.
int fadeNormalize(int seq) {
  seq %= 102;
  if (seq <= 51) {
    return 5 * seq;
  } else {
    return 255 - 5*(seq-51);
  }
}

