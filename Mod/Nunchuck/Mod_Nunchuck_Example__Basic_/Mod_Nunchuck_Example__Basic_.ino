/* Mod Nunchuck -- written by Craig Durkin / Comingle. */
/* This software comes pre-loaded on Comingle Multivibe sex toys */

#include <Wire.h>
#include <OSSex.h>

bool clicked = false;

void setup() {
  // Set ID. ALPHA (0) (lilypad boards) or BETA (1) (Dilduino Boards) are current options.
  Toy.setID(BETA);
  
  // Button will increase/decrease power by 20%
  Toy.setPowerScale(0.03);
  Toy.setTimeScale(0.02);
  


  
  Toy.setHackerPort(HACKER_PORT_I2C); // should be HACKER_PORT_I2C but for some reason not compiling
  
//  pinMode(8, OUTPUT);
//    pinMode(12, OUTPUT);
//    digitalWrite(8, HIGH);
//    digitalWrite(12, LOW);
//    
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
byte joyy, joyx, cbut, zbut;

void loop() {
  
  //
  
  
  
  
  if (nunchuck_get_data()) {
    joyy = nunchuck_joyy();
    joyx = nunchuck_joyx();
    zbut = nunchuck_zbutton();
    cbut = nunchuck_cbutton();
  } else {
    joyy = joyx = 128;
    zbut = cbut = -5;
  }
  
  Serial.print("Zbut  ");
  Serial.print(zbut);
  Serial.print("/t");
Serial.print ("cbut ");
Serial.print (cbut);
  
  
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
}






