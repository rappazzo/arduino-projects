#include <CapacitiveSensor.h>
CapacitiveSensor capSensor = CapacitiveSensor(4, 2);

int threshold = 1000;
const int LED = 12;

void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
}

void loop() {
  long sensorValue = capSensor.capacitiveSensor(30);
  Serial.println(sensorValue);
  digitalWrite(LED, sensorValue > threshold ? HIGH : LOW);
  delay(10);

}
