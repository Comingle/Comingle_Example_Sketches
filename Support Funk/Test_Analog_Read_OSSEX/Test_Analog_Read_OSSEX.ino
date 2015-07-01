/* Mod Nunchuck -- written by Craig Durkin / Comingle. */
/* This software comes pre-loaded on Comingle Multivibe sex toys */

#include <Wire.h>
#include <OSSex.h>

bool clicked = false;

int inputPin = A9;
void setup() {
  // Set ID. ALPHA (0) (lilypad boards) or BETA (1) (Dilduino Boards) are current options.
  Toy.setID(BETA);
  
  // Button will increase/decrease power by 20%
  Toy.setPowerScale(0.03);
  Toy.setTimeScale(0.02);
  


  
  Toy.setHackerPort(HACKER_PORT_AIN); // should be HACKER_PORT_I2C but for some reason not compiling
  
//  pinMode(8, OUTPUT);
//    pinMode(12, OUTPUT);
//    digitalWrite(8, HIGH);
//    digitalWrite(12, LOW);

pinMode(inputPin ,INPUT);
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
  
Serial.println (analogRead(inputPin));  
}






