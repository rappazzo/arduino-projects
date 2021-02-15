#include <TimerOne.h>


int BUTTON = 2;
int GREEN  = 3;
int YELLOW = 4;
int RED    = 5;
int BLUE   = 6;

int GREEN_SECS = 5;
int YELLOW_SECS = 2;
int RED_SECS = 5;

volatile int pressed = 0;
volatile int current_seconds = 0;
volatile int current_light = GREEN;


void lightUp(int lit) {
  digitalWrite(GREEN,  lit == GREEN  ? HIGH : LOW);
  digitalWrite(YELLOW, lit == YELLOW ? HIGH : LOW);
  digitalWrite(RED,    lit == RED    ? HIGH : LOW);
}

int getCurrentLightTimeLimit() {
  if (current_light == GREEN) {
    return GREEN_SECS;
  } else if (current_light == YELLOW) {
    return YELLOW_SECS;
  } else {
    return RED_SECS;
  }
}

void checkForNextLight() {
  int secs = getCurrentLightTimeLimit();
  if (current_seconds > secs) {
     current_light = (((current_light + 1) - GREEN) % 3) + GREEN;
     current_seconds = 0;
  }
}

void lightNext() {
  lightUp(current_light);
  current_seconds++;
  checkForNextLight();
}

void button_pressed() {
  pressed = 1;
}

void setup() {
  pinMode(GREEN,  OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(RED,    OUTPUT);
  pinMode(BLUE,   OUTPUT);
  pinMode(BUTTON, INPUT);
  attachInterrupt(digitalPinToInterrupt(BUTTON), button_pressed, RISING);
  
  Timer1.initialize(1000000);
  // set a timer of length 1 sec (1_000_000 microseconds)
  Timer1.attachInterrupt( lightNext );
}

void loop() {
  // put your main code here, to run repeatedly:
  if (pressed == 1) {
    digitalWrite(BLUE, HIGH);
    delay(4000);
    digitalWrite(BLUE, LOW);
    pressed = 0;
  }
  /*
  lightUp(GREEN);
  delay(700);
  lightUp(YELLOW);
  delay(300);
  lightUp(RED);
  delay(700);
  */
}
