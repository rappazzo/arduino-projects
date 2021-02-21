const int SWITCH_PIN = 2;
const int MOTOR_PIN = 9;

void setup() {
  pinMode(MOTOR_PIN, OUTPUT);
  pinMode(SWITCH_PIN, INPUT);
}

void loop() {
  digitalWrite(MOTOR_PIN, digitalRead(SWITCH_PIN));
}
