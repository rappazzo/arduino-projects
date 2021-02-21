const int CONTROL_1 = 2;
const int CONTROL_2 = 3;
const int ENABLE = 9;
const int DIR_SWITCH = 4;
const int ON_OFF_SWITCH = 5;
const int POT = A0;

int onOffState = 0;
int prevOnOff = 0;
int dirState = 0;
int prevDir = 0;

int motorEnabled = 0;
int motorSpeed = 0;
int motorDir = 1;


void setup() {
  pinMode(DIR_SWITCH, INPUT);
  pinMode(ON_OFF_SWITCH, INPUT);
  pinMode(CONTROL_1, OUTPUT);
  pinMode(CONTROL_2, OUTPUT);
  pinMode(ENABLE, OUTPUT);

  digitalWrite(ENABLE, LOW);
}

void loop() {
  onOffState = digitalRead(ON_OFF_SWITCH);
  delay(1);
  dirState = digitalRead(DIR_SWITCH);
  motorSpeed = analogRead(POT) / 4;

  if (onOffState != prevOnOff) {
    if (onOffState == HIGH) {
      motorEnabled = !motorEnabled;
    }
  }

  if (dirState != prevDir) {
    if (dirState == HIGH) {
      motorDir = !motorDir;
    }
  }
  if (motorDir == 1) {
    digitalWrite(CONTROL_1, HIGH);
    digitalWrite(CONTROL_2, LOW);
  } else {
    digitalWrite(CONTROL_1, LOW);
    digitalWrite(CONTROL_2, HIGH);
  }

  if (motorEnabled == 1) {
    analogWrite(ENABLE, motorSpeed);
  } else {
    analogWrite(ENABLE, 0);
  }

  prevDir = dirState;
  prevOnOff = onOffState;

}
