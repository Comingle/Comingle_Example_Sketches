//Record a series of analog inputs
//and playback to the vibe motors
//based on servo record playback at adafruit
// http://www.adafruit.com/products/1404

/* Include the library */
#include <OSSex.h>
#include <ADCTouch.h>
#include <Wire.h> // fickle library you have to include
#include <EEPROM.h>



//Cap touch sensing Setup
int led = 13;

int ref0, ref1;       //reference values to remove offset
int qvalue0;
int qvalue1;

int controlval0 = 0;
int controlval1 = 0;


//Record Playback Items
//#define CALIB_MAX 512
//#define CALIB_MIN 100
#define SAMPLE_DELAY 50 // in ms// qtouch = 50ms always  at 100samples with one pade 100ms with two pads
#define MAX_SAMPLES 512
char recording[MAX_SAMPLES];
uint8_t recButtonPin = 4;
//uint8_t playButtonPin = 10; 
uint8_t playBackPin = 10;//middle motor, all motors are 5,10,11
//uint8_t servoPin = 9;
//uint8_t feedbackPin = A0;
uint8_t ledPin = 13;

bool modeRec = false;

bool modePlay = false;

  
void setup() {
   // Set ID. ALPHA (0) or BETA (1) are current options.
  // The sketch won't compile until you set this!
  Toy.setID(BETA);
  
  //QTOUCH setup
  // No pins to setup, pins can still be used regularly, although it will affect readings

  //These are reading the internal cap-touch analog inputs on the dilduino
  ref0 = ADCTouch.read(A2, 500);    //create reference values to
  ref1 = ADCTouch.read(A3, 500);      //account for the capacitance of the pad
  pinMode(led, OUTPUT);

  ////////////
  // Blip all the motors and flash the LED to show that everything is working and the device is on.
  startupSequence();
  
  ///////////
  //RecPlay Items
  Serial.begin(9600);
  pinMode(recButtonPin, INPUT);
//  digitalWrite(recordButtonPin, HIGH);
//  pinMode(playButtonPin, INPUT);
//  digitalWrite(playButtonPin, HIGH);
  pinMode(ledPin, OUTPUT);
  
    attachClicks();


}

void loop() {
  
    captouchProcessor(true);  
    //analogWrite(playBackPin,controlval0);
    
    modeCheck();

}

//A large switch statement that helps us determine modes
//that need to be run outside of OSSEX patterns
   void modeCheck(){
      
      
      if(modeRec){
        recordPattern(playBackPin);
      }
      if(modePlay){
           playPattern(playBackPin);

      }
    }


void  attachClicks() {
  // Set up the button click handlers
  Toy.attachClick(click);
  Toy.attachDoubleClick(doubleClick);
  Toy.attachLongPressStart(longPress);
}


// Click handler. Currently moves to next pattern.
void click() {
modePlay=true;
}

// Double click handler Currently increases power.
void doubleClick() {

}

// Click and hold handler. Currently decreases power.
void longPress() {
  modeRec=true;
}


void halt() {
  Toy.stop();
}

int captouchProcessor(bool printstuff) {

  long start =  millis();
//qvalue0=43;
  qvalue0 = ADCTouch.read(A2);   //no second parameter
  //qvalue1 = ADCTouch.read(A3);     //   --> 100 samples

  qvalue0 -= ref0;       //remove offset
 // qvalue1 -= ref1;
controlval0 = constrain(qvalue0 * 4, 0, 254);
 // controlval1 = constrain(qvalue1 * 4, 0, 254);
  
if(printstuff){
  Serial.print(qvalue0 > 40);    //return pressed or not pressed
  Serial.print("\t");
//  Serial.print(qvalue1 > 40);
  Serial.print("\t\t");
  Serial.print(qvalue0);             //return value
  Serial.print("\t");
//  Serial.print(qvalue1);
    Serial.print("\t");
    
      Serial.print("\t Rec butt state");
Serial.print(digitalRead(recButtonPin));

        Serial.print(" calc time ");



long calctime= millis()-start;
    Serial.println(calctime);    

}
    //    delay(1); //delay is for the cap touch sensing
  return controlval0;
}


int captouchProcessorOrig(bool printstuff) {

  long start =  millis();

  qvalue0 = ADCTouch.read(A2);   //no second parameter
  qvalue1 = ADCTouch.read(A3);     //   --> 100 samples

  qvalue0 -= ref0;       //remove offset
  qvalue1 -= ref1;
controlval0 = constrain(qvalue0 * 4, 0, 254);
  controlval1 = constrain(qvalue1 * 4, 0, 254);
  
if(printstuff){
  Serial.print(qvalue0 > 40);    //return pressed or not pressed
  Serial.print("\t");
  Serial.print(qvalue1 > 40);
  Serial.print("\t\t");
  Serial.print(qvalue0);             //return value
  Serial.print("\t");
  Serial.print(qvalue1);
    Serial.print("\t");
        Serial.print(" calc time ");

long calctime= millis()-start;
    Serial.println(calctime);    

}
    //    delay(1); //delay is for the cap touch sensing
  return controlval0;
}

// Cycle through all the outputs, turn the LED on and leave it on to show that we're on
void startupSequence() {
  int outs = Toy.device.outCount;
  int outInterval = 100 / outs;

  Toy.setLED(0, 128);

  for (int i = 0; i < outs; i++) {
    Toy.setOutput(i, 100 + outInterval * i);
    delay(100);
    Toy.setOutput(i, 0);
    delay(50);
  }
  for (int i = 0; i < 3; i++) {
    Toy.setLED(0, 0);
    delay(100);
    Toy.setLED(0, 128);
    delay(100);
  }
}



void playPattern(uint8_t playback) {
  uint16_t addr = 0;
  Serial.println("Playing");

  while (true) {    

    //Uncomment if want to store to EEPROM
//    uint8_t x = EEPROM.read(addr); //read it from memory
//    Serial.print("Read EE: "); Serial.print(x);
    
    
    uint8_t x = recording[addr];
    
    Serial.print("Read recording: "); Serial.print(x);
    //Look for end of pattern flag!
    if (x == 255) break;
    
    

    Serial.print(" @ "); Serial.println(addr);
   analogWrite(playBackPin,x);
    delay(SAMPLE_DELAY);
    addr++;
    if (addr == 512) break;
  }
  Serial.println("Done Playback");
  //turn it back off
     analogWrite(playBackPin,0);

modePlay = false;
  //delay(250);  
}

void recordPattern(uint8_t playBack) {
  uint16_t addr = 0;
  
  Serial.println("Recording");
  digitalWrite(ledPin, HIGH);
 
  while (!digitalRead(recButtonPin)) {    

     uint16_t a = 
     (uint16_t)captouchProcessor(true);
       
       //for analogread 
    // int     a = analogRead(A2);
          
     Serial.print("Read analog: "); Serial.print(a);
     
     
    /* if (a < CALIB_MIN) a = CALIB_MIN;
     if (a > CALIB_MAX) a = CALIB_MAX;
     a = map(a, CALIB_MIN, CALIB_MAX, 0, 254);
     */
     
     //for analogread
   //      a = map(a, 0, 1024, 0, 254);

     Serial.print(" -> "); Serial.print(a);
     Serial.print(" @ "); Serial.println(addr);
     
             analogWrite(playBackPin,a);

     
     recording[addr] = a;
     //uncomment if want to store on eeprom
     //EEPROM.write(addr, a);
     
     
     addr++;
     if (addr == 512) break;
      //turn back on for regular analog read
   //  delay(SAMPLE_DELAY); // Qtouch already has a 100ms delay inherently 
  }
   //turn off playback
        analogWrite(playBackPin,0);
        
        //If we exit the loop early, then set as 255 to flag end of pattern recorded
  if (addr != 512) {
    //EEPROM.write(addr, 255);
  recording[addr] = 255;
  }

//turn off pin
  digitalWrite(ledPin, LOW);

  Serial.println("Done rec");
  delay(250);
  modeRec = false;

}
