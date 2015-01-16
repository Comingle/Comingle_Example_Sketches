/* Multivibe Sketch v0.2 -- written by Craig Durkin / Comingle. */
/* This software comes pre-loaded on Comingle Multivibe sex toys */

#include <Wire.h>
#include <OSSex.h>

bool clicked = false;

void setup() {
  // Set ID. ALPHA (0) or BETA (1) are current options.
  Toy.setID(BETA);
  
  // Button will increase/decrease power by 20%
  Toy.setPowerScale(0.03);
  Toy.setTimeScale(0.02);
  
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
  
  pinMode(8, OUTPUT);
    pinMode(12, OUTPUT);
    digitalWrite(8, HIGH);
    digitalWrite(12, LOW);
    
    nunchuck_init();
  
  Serial.begin(9600);
  
}

static uint8_t nunchuck_buf[6];
static void nunchuck_init()
{ 
    Wire.begin();                // join i2c bus as master
    Wire.beginTransmission(0x52);// transmit to device 0x52

    Wire.write((uint8_t)0x40);// sends memory address
    Wire.write((uint8_t)0x00);// sends sent a zero.  

    Wire.endTransmission();// stop transmitting
}

static char nunchuk_decode_byte (char x)
{
    x = (x ^ 0x17) + 0x17;
    return x;
}

static void nunchuck_send_request()
{
    Wire.beginTransmission(0x52);// transmit to device 0x52
    Wire.write((uint8_t)0x00);// sends one byte
    Wire.endTransmission();// stop transmitting
}

static int nunchuck_get_data()
{
    int cnt=0;
    Wire.requestFrom (0x52, 6);// request data from nunchuck
    while (Wire.available ()) {
        // receive byte as an integer
        nunchuck_buf[cnt] = nunchuk_decode_byte( Wire.read() );

        cnt++;
    }
    nunchuck_send_request();  // send request for next data payload
    // If we recieved the 6 bytes, then go print them
    if (cnt >= 5) {
        return 1;   // success
    }
    return 0; //failure
}

static int nunchuck_joyy()
{
    return nunchuck_buf[1];
}

static int nunchuck_joyx()
{
    return nunchuck_buf[0]; 
}

static int nunchuck_zbutton()
{
    return ((nunchuck_buf[5] >> 0) & 1) ? 0 : 1;
}

// returns zbutton state: 1=pressed, 0=notpressed
static int nunchuck_cbutton()
{
    return ((nunchuck_buf[5] >> 1) & 1) ? 0 : 1;
}


int samples[2][6];
int movingAvg[2];
int lastMovingAvg[2];
int baselineMovingAvg[2];
int baselines[2][6];
int trends[2];
byte joyyB, joyxB, cbut, zbut;

void loop() {
  
  //Each motor is given a virtual "position"
  //unit is multiplied by 1000
  float motor0pos = 0.0;
  float motor1pos = 1000;
  float motor2pos = 2000;
  
  //For this first demo we are going to have the Vibration "position"
 // Mapped directly to the position of the joystick. 
 //e.g. When joystick is all the way UP, motor 2 is on, when in the middle motor 1 is on
 
  
 //Update nunchuck position 
  if (nunchuck_get_data()) {
    joyyB = nunchuck_joyy();
    joyxB = nunchuck_joyx();
    zbut = nunchuck_zbutton();
    cbut = nunchuck_cbutton();
  } else {
    joyyB = joyxB = 128;
    zbut = cbut = 0;
  }
  
  int joyy= joyyB;
  //Map the joystick to the range of our virtual positions 0-2000
 joyy= map(joyy,30,225,0,2000);
  //calculate motor scaling factors
    
   //M0
    //calculate distance between joystick and this motor, to set the powerscale)
  float motor0scale = 
  1000-abs(motor0pos-joyy);
 motor0scale =  constrain(motor0scale, 0,1000);
 motor0scale =  map(motor0scale, 0,1000, 0,255);
  
  Toy.setOutput(0,motor0scale);
  Serial.print("  m0 ");
  Serial.print(motor0scale);
  
  //M1
      //calculate distance between joystick and this motor, to set the powerscale)
  float motor1scale = 
  1000-abs(motor1pos-joyy);
 motor1scale =  constrain(motor1scale, 0,1000);
 motor1scale =  map(motor1scale, 0,1000, 0,255);
  
  Toy.setOutput(1,motor1scale);
  Serial.print("  m1 ");
  Serial.print(motor1scale);
  //M2
      //calculate distance between joystick and this motor, to set the powerscale)
  float motor2scale = 
  1000-abs(motor2pos-joyy);
  motor2scale = constrain(motor2scale, 0,1000);
  motor2scale = map(motor2scale, 0,1000, 0,255);
  
  Toy.setOutput(0,motor2scale);
  Serial.print("  m2 ");
  Serial.println(motor2scale);
  
  /*
  char command[1];
  byte val;
  int out0 = joyy;
  int out1 = joyx;

  if (cbut) {
    Toy.cyclePattern();
    delay(200);
  }
  
  if (zbut) {
    Toy.stop();
    delay(200);
  }
  

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
  Serial.println(movingAvg[0]);
  // if moving average is roughly near middle point (512), throw it on stack of baseline moving averages
  for (int p = 0; p < 2; p++) {
    if (108 <= movingAvg[p] && movingAvg[p] <= 148) {
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
  
  for (int q = 0; q < 2; q++) {
    if (108 <= baselineMovingAvg[q] && baselineMovingAvg[q] <= 148) {
      trends[0] = out0 - baselineMovingAvg[0];
      trends[1] = out1 - baselineMovingAvg[1];
      if (trends[0] > 10) {
        Toy.increaseTime();
      } else if (trends[0] < -10) {
        Toy.decreaseTime();
      }
      if (trends[1] > 10) {
        Toy.increasePower();
      } else if (trends[1] < -10) {
        Toy.decreasePower();
      }
    }
  }
  
  if (Serial.available() > 0) {
    Serial.readBytes(command,1);
    if (command[0] == 'l') {
      val = Serial.parseInt();
      Toy.setLED(0,val);
      Serial.println(val);
    } else if (command[0] == '0' || command[0] == '1' || command[0] == '2') {
      val = Serial.parseInt();
      Toy.setOutput(command[0], val);
      Serial.println(val);
    } else if (command[0] == '-') {
      int out = Serial.parseInt();
      out *= -1;
      val = Serial.parseInt();
      Toy.setOutput(out,val);
    } else if (command[0] == 'p') {
      Serial.println(Toy.decreasePower());
    } else if (command[0] == 'P') {
      Serial.println(Toy.increasePower());
    } else if (command[0] == 't') {
      Serial.println(Toy.decreaseTime());
    } else if (command[0] == 'T') {
      Serial.println(Toy.increaseTime());
    } else if (command[0] == 'r') {
      val = Serial.parseInt();
      Toy.runPattern(val);
      Serial.println(Toy.getPattern());
    } else if (command[0] == 'g') {  
      Serial.println(Toy.getPattern());
    } else if (command[0] == 's') {
      Toy.stop();
    } else if (command[0] == 'c') {
      Toy.cyclePattern();
      Serial.println(Toy.getPattern());
    }
  }
 
  delay(100);
  movingAvg[0] = movingAvg[1] = baselineMovingAvg[0] = baselineMovingAvg[1] = 0;
*/
delay(10);
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
  Toy.setPowerScale(0.2);
  Toy.increasePower();
  Toy.setPowerScale(0.03);
}

void longPress() {
  Toy.setPowerScale(0.2);
  Toy.decreasePower();
  Toy.setPowerScale(0.03);
}

// Begin Pattern functions

int step[3];

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

  // sequence runs: 0 -> 255 -> 0 in 5 step increments.
  // 0 -> 255: 51 steps.
  // 255 -> 0: 51 steps;
  // -> 102 steps per output, 306 steps total.
  // normalize sequence
  seq %= 307;
  
  // output 0
  if (seq <= 51) {
    step[0] = 0;
    step[1] = fadeNormalize(seq);
    // output 0 and 1
  } else if (seq <= 154) {
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
  } else if (seq <= 256) {
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
  
  step[2] = 30;
  return step;
}

int* first(int seq) {
  step[0] = 0;
  step[1] = 100;
  step[2] = 50;
  return step;
}

int* second(int seq) {
  step[0] = 1;
  step[1] = 100;
  step[2] = 50;
  return step;
}

int* third(int seq) {
  step[0] = 2;
  step[1] = 100;
  step[2] = 50;
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
  seq %= 307;
  
  if (seq <= 102) {
    step[0] = 0;
  } else if (seq <= 204) {
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




