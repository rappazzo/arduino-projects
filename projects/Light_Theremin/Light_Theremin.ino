
int sensorValue;
int sensorLow = 1023;
int sensorHigh = 0;

const int BUTTON = 2;
const int LED_PIN = 13;
volatile boolean on = false;

void button_pressed() {
  on = !on;
}

void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);
  
  pinMode(BUTTON, INPUT);
  attachInterrupt(digitalPinToInterrupt(BUTTON), button_pressed, RISING);

  while (millis() < 5000) {
    sensorValue = analogRead(A0);
    if (sensorValue > sensorHigh) {
      sensorHigh = sensorValue;
    }
    if (sensorValue < sensorLow) {
      sensorLow = sensorValue;
    }
    digitalWrite(LED_PIN, LOW);
  }
}

void loop() {
  if (on) {
    sensorValue = analogRead(A0);
    int pitch = map(sensorValue, sensorLow, sensorHigh, 50, 4000);
    tone(8, pitch, 20);
  }
  delay(10);
}
