int ledPins[] = {8,9,10,11,12,13};
int motorPins[] = {2,3,4,5,6,7};
int i;

void setup() {
  Serial.begin(9600);
  for (i = 8; i<=13; i++) {
    pinMode(i, OUTPUT);
  }
  for (i = 2; i<=7; i++) {
    pinMode(i, OUTPUT);
  }
}

void loop() {
  for (i = 13; i>=8; i--) {
    digitalWrite(i, LOW);
    //digitalWrite(i-6, HIGH);
    
    // delay(100);
    digitalWrite(i-1, LOW);
    //digitalWrite(i-5, HIGH);
     
    delay(50);
 
    digitalWrite(i, HIGH);
    //digitalWrite(i-6, LOW);
     digitalWrite(i-1, HIGH);
    //digitalWrite(i-5, LOW);*/
  } 
  /* for (i = 2; i<=7; i++) {
    digitalWrite(i, HIGH);
    Serial.println(i);
    delay(250);
    digitalWrite(i, LOW);
  } */
}
