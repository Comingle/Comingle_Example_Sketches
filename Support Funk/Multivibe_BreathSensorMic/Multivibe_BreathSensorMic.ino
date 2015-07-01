/* Multivibe software -- written by Craig Durkin / Comingle. First released Aug 17, 2014 */
/* This software comes pre-loaded on Comingle Multivibe sex toys */

#include <OSSex.h>

bool clicked = false;
#define LED_N_SIDE A2
#define LED_P_SIDE A3

int darkamount = 0;

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
}

unsigned int timeScale = 100;
unsigned int powerScale = 100;
int samples[2][6];
int movingAvg[2];
int lastMovingAvg[2];
int baselineMovingAvg[2];
int baselines[2][6];
int trends[2];
void loop() {
  int out0 = Toy.getInput(0);
  int out1 = Toy.getInput(1);
  // get a moving average of past 6 samples
  for (int i = 0; i < 5; i++) {
    samples[0][i] = samples[0][i+1];
    samples[1][i] = samples[1][i+1];
  }
  samples[0][5] = out0;
  samples[1][5] = out1; 
  for (int j = 0; j < 6; j++) {
    movingAvg[0] += samples[0][j];
    movingAvg[1] += samples[1][j];
  }
  movingAvg[0] /= 6;
  movingAvg[1] /= 6; 
  
  // if moving average is roughly near middle point (512), throw it on stack of baseline moving averages
  for (int p = 0; p < 2; p++) {
    if (690 <= movingAvg[p] && movingAvg[p] <= 850) {
      for (int k = 0; k < 5; k++) {
        baselines[p][k] = baselines[p][k+1];
      }
      baselines[p][5] = movingAvg[p];
    }
  }
  // calculate baseline to offset our sensor value.
  for (int m = 0; m < 6; m++) {
      baselineMovingAvg[0] += baselines[0][m];
      baselineMovingAvg[1] += baselines[1][m];
  }
  baselineMovingAvg[0] /= 6;
  baselineMovingAvg[1] /= 6;
  trends[0] = out0 - baselineMovingAvg[0];
  trends[1] = out1 - baselineMovingAvg[1];
  
  if (trends[0] > 10) {
    timeScale += 5;
  } else if (trends[0] < -10) {
    if (timeScale >= 1) {
      timeScale -= 5;
    }
  }
  if (trends[1] > 10) {
    powerScale += 100;
  } else if (trends[1] < -10) {
    if (powerScale >= 100) {
      powerScale -= 100;
    }
  }
  Serial.println(out0);
 // Serial.print('|');
 // Serial.println(out1);
  delay(100);
  movingAvg[0] = movingAvg[1] = baselineMovingAvg[0] = baselineMovingAvg[1] = 0;
}

int timeSanitize(unsigned int input, unsigned int low, unsigned int high) {
  int output = input * timeScale / 100; 
  int safe = constrain(output, low, high);
  if (safe > output) { // we're low
    while (safe > input * timeScale / 100) {
      timeScale+=1;
    }
  } else if (safe < output) { // we're high
    while (safe < input * timeScale / 100) {
      timeScale-=1;
    }
  }
  return safe;
}

int powerSanitize(unsigned int input, unsigned int low, unsigned int high) {
  int output = input * powerScale / 100; 
  int safe = constrain(output, low, high);
  if (safe > output) { // we're low
    while (safe > input * powerScale / 100) {
      powerScale+=1;
    }
  } else if (safe < output) { // we're high
    while (safe < input * powerScale / 100) {
      powerScale-=1;
    }
  }
  return safe;
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
  clicked = true;
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

// Turn on all outputs slightly offset from each other. Continues to generate steps even after outputs are on so that the power can be adjusted.
int* flicker(int seq) {
  if (seq > 2) {
    step[2] = timeSanitize(200, 20, 500);
  } else {
    step[2] = timeSanitize(20, 20, 200);
  }
  seq %= 3;
  step[0] = seq;
  step[1] = powerSanitize(80, 0, 255);
 
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
  
  step[2] = timeSanitize(70, 20, 140);
  return step;
}

// Opposite of pulse() -- turn on all outputs, randomly blip one off
int* pulse2(int seq) {
  if (seq % 2) {
    step[0] = -1;
    step[1] = timeSanitize(100, 0, 255);
  } else {
    step[0] = random(0,3);
    step[1] = 0;
  }
  step[2] = timeSanitize(100, 20, 200);
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
  
  step[2] = timeSanitize(30, 20, 200);
  return step;
}

int* first(int seq) {
  step[0] = 0;
  step[1] = powerSanitize(100, 0, 255);
  step[2] = 50;
  return step;
}

int* second(int seq) {
  step[0] = 1;
  step[1] = powerSanitize(100, 0, 255);
  step[2] = 50;
  return step;
}

int* third(int seq) {
  step[0] = 2;
  step[1] = powerSanitize(100, 0, 255);
  step[2] = 50;
  return step;
}

int* weird2(int seq) {
  step[0] = 0;
  step[2] = timeSanitize(30, 20, 200);
  step[1] = round(127*cos(tan(tan(seq/(8*PI)))-PI/2)+127);
  return step;
}

int* weird3(int seq) {
  step[0] = 2;
  step[2] = timeSanitize(30, 20, 200);
  step[1] = round(50*(cos(seq/(8*PI)+PI/2) + sin(seq/2))+100);
  return step;
}

int *fadeCos(int seq) {
  step[0] = -1;
  step[2] = timeSanitize(50, 20, 200);
  step[1] = round(127 * cos((seq / (8*PI))-PI) + 127);
  return step;
}

int* fadeSequence(int seq) {
  step[2] = timeSanitize(30, 20, 200);

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
