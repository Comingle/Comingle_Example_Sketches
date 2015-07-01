/*
  ReadAllAnalogInputs_LilyUSB
  Check out all the sensor on a LilyUSB
 This example code is in the public domain.
 */

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  
  //For comingle shut off all the motors in the multivibe
  
    pinMode(13, OUTPUT);   
  pinMode(11, OUTPUT);     
    pinMode(10, OUTPUT);     

  pinMode(9, OUTPUT);     
  pinMode(3, OUTPUT); 


digitalWrite(3, LOW);
digitalWrite(9, LOW);
digitalWrite(10, LOW);
digitalWrite(11, LOW);
digitalWrite(13, HIGH); //lets me know it is on!
  
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int sensorValue0 = analogRead(A0);
  int sensorValue1 = analogRead(A1);
  int sensorValue2 = analogRead(A2);
  int sensorValue3 = analogRead(A3); //For comingle this is D- on USB breakout
  int sensorValue4 = analogRead(A4); //  For comingle this is D+ on USB breakout
  int sensorValue5 = analogRead(A5);

  // print out the values you read:

   Serial.print("  A3: ");
  Serial.print(sensorValue3); //Left and right
   Serial.print("  A4: ");
  Serial.print(sensorValue4); //Vertical

  
  Serial.println();
  
  
}
