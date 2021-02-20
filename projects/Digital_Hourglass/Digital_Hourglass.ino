const int SWITCH_PIN = 9;
unsigned long previousTime = 0;
int prevSwitchState = 0;
int currentLed = 7;
long INTERVAL = 500;

void lightAll() {
  for (int x = 7; x >= 2; x--) {
    digitalWrite(x, HIGH);
  }
}

void setup() {
  for (int x = 2; x < 8; x++) {
    pinMode(x, OUTPUT);
  }
  lightAll();
  pinMode(SWITCH_PIN, INPUT);
  //Serial.begin(9600);
}

void loop() {
  unsigned long currentTime = millis();
  if (currentTime - previousTime > INTERVAL) {
    previousTime = currentTime;
    digitalWrite(currentLed, LOW);
    currentLed--;
    if (currentLed == 0) {
      tone(8, 294, 800);
      delay(800);
      tone(8, 278, 600);
      delay(600);
      for (int i  = 0; i <  25; i++) {
         tone(8, 315, 40);
         delay(40);
         tone(8, 311, 40);
         delay(40);
      }
    }
  }
  int switchState = digitalRead(SWITCH_PIN);
  if (switchState != prevSwitchState) {
    lightAll();
    currentLed = 7;
    previousTime = currentTime;
  }
  prevSwitchState = switchState;

}
