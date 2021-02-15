#include <Servo.h>

//#define DEBUG

Servo myServo;
int const POT_PIN = A0;
int potVal;
int angle;

void setup() {
  myServo.attach(9);

  Serial.begin(9600);
}

void loop() {
  potVal = analogRead(POT_PIN);

  angle = map(potVal, 0, 889, 0, 36) * 5;

  #ifdef DEBUG
  Serial.print("potVal: ");
  Serial.print(potVal);
  Serial.print(", angle: ");
  Serial.print(angle);
  Serial.println();
  #endif
  
  myServo.write(angle);
  delay(100);
}
