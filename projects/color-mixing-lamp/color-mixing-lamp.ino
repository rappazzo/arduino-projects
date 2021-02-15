//#define DEBUG;

int RED   = 9;
int GREEN = 11;
int BLUE  = 10;

int RED_SENSOR   = A0;
int GREEN_SENSOR = A1;
int BLUE_SENSOR  = A2;

int redVal   = 0;
int greenVal = 0;
int blueVal  = 0;


void setup() {
  Serial.begin(9600);
  pinMode(GREEN,  OUTPUT);
  pinMode(RED,    OUTPUT);
  pinMode(BLUE,   OUTPUT);
}

void debug(const String &str) {
  #ifdef DEBUG
  Serial.print(str);
  Serial.print(" Values - red: ");
  Serial.print(redVal);
  Serial.print(", green: ");
  Serial.print(greenVal);
  Serial.print(", blue: ");
  Serial.print(blueVal);
  Serial.println();
  #endif
}

void loop() {
  redVal = analogRead(RED_SENSOR);
  delay(5);
  greenVal = analogRead(GREEN_SENSOR);
  delay(5);
  blueVal = analogRead(BLUE_SENSOR);

  debug("Raw Sensor");

  redVal /= 4;
  greenVal /= 4;
  blueVal /= 4;
  debug("Normalized");

  analogWrite(RED, redVal);
  analogWrite(GREEN, greenVal);
  analogWrite(BLUE, blueVal);
  delay(100);
}
