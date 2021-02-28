#include <Servo.h>

Servo lock;

const int PIEZO = A0;
const int SWITCH = 2;
const int YELLOW = 3;
const int GREEN = 4;
const int RED = 5;

int knockVal;
int switchVal;

const int QUIET = 10;
const int LOUD = 100;

boolean locked = false;
int numberOfKnocks = 0;

void setup() {
  lock.attach(9);
  pinMode(YELLOW, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(SWITCH, INPUT);
  Serial.begin(9600);

  digitalWrite(GREEN, HIGH);
  lock.write(0);
  Serial.println("The box is unlocked.");
}

void loop() {
  if (locked == false) {
    switchVal = digitalRead(SWITCH);
    if (switchVal == HIGH) {
      locked = true;
      digitalWrite(GREEN, LOW);
      digitalWrite(RED, HIGH);
      lock.write(90);
      Serial.println("The box is locked");
      delay(1000);
    }
  }
  if (locked == true) {
    knockVal = analogRead(PIEZO);
    if (numberOfKnocks < 3 && knockVal > 0) {
      if (checkKnock(knockVal) == true) {
        numberOfKnocks++;
      }
      Serial.print(3 - numberOfKnocks);
      Serial.println(" more knocks to go");
    }
    if (numberOfKnocks >= 3) {
      locked = false;
      lock.write(0);
      delay(20);
      digitalWrite(GREEN, HIGH);
      digitalWrite(RED, LOW);
      Serial.println("The box is unlocked.");
      numberOfKnocks = 0;
    }
  }
}

boolean checkKnock(int value) {
  if (value > QUIET && value < LOUD) {
    digitalWrite(YELLOW, HIGH);
    delay(50);
    digitalWrite(YELLOW, LOW);
    Serial.print("   >> Valid knock value: ");
    Serial.println(value);
    return true;
  } else {
    Serial.print("   >> Invalid knock value: ");
    Serial.println(value);
    return false;
  }
}
