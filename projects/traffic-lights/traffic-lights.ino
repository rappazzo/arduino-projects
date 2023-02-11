#include <TimerOne.h>


int BUTTON = 2;
int GREEN  = 3;
int YELLOW = 4;
int RED    = 5;
int BLUE   = 6;
int IR     = 8;

int GREEN_SECS = 5;
int YELLOW_SECS = 2;
int RED_SECS = 5;
int MAX_CYCLES = 5;

volatile int pressed = 0;
volatile int current_seconds = 0;
volatile int current_light = RED;
volatile int cycle_count = 0;
volatile int in_cycle = 1;
volatile int off_cycle_count = 0;
// The BLUE LED is just an indicator that things are still working - basically a debugging helper
int BLUE_ENABLED = 1;


void light_up(int lit) {
  digitalWrite(GREEN,  lit == GREEN  ? HIGH : LOW);
  digitalWrite(YELLOW, lit == YELLOW ? HIGH : LOW);
  digitalWrite(RED,    lit == RED    ? HIGH : LOW);
}

void all_off() {
  digitalWrite(GREEN,  LOW);
  digitalWrite(YELLOW, LOW);
  digitalWrite(RED,    LOW);
}

int get_current_light_time_limit() {
  if (current_light == GREEN) {
    return GREEN_SECS;
  } else if (current_light == YELLOW) {
    return YELLOW_SECS;
  } else {
    return RED_SECS;
  }
}

void check_for_next_light() {
  int secs = get_current_light_time_limit();
  if (current_seconds > secs) {
     current_light = (((current_light + 1) - GREEN) % 3) + GREEN;
     current_seconds = 0;
     if (current_light == RED) {
        cycle_count++;
        if (cycle_count >= MAX_CYCLES) {
          in_cycle = 0;
          cycle_count = 0;
          all_off();
          off_cycle_count = 0;
          if (BLUE_ENABLED) {
            digitalWrite(BLUE, LOW);
          }
        }
     }
  }
}

void start_light_cycle() {
  cycle_count = 0;
  current_light = RED;
  current_seconds = 0;
  light_next();
}

void set_button_pressed() {
  pressed = 1;
}

void button_pressed() {
  pressed = 0;
  in_cycle = 1;
  start_light_cycle();
}

void motion_detected() {
  in_cycle = 1;
  start_light_cycle();
}

void light_next() {
  if (in_cycle) {
    light_up(current_light);
    current_seconds++;
    check_for_next_light();
  } else {
    off_cycle_count++;
    if (BLUE_ENABLED) {
      digitalWrite(BLUE, (off_cycle_count % 2 == 0) ? HIGH : LOW);
    }
  }
}

void setup() {
  pinMode(GREEN,  OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(RED,    OUTPUT);
  if (BLUE_ENABLED) {
    pinMode(BLUE,   OUTPUT);
  }
  pinMode(BUTTON, INPUT);
  pinMode(IR,     INPUT);
  attachInterrupt(digitalPinToInterrupt(BUTTON), set_button_pressed, RISING);
  
  // set a timer of length 1 sec (1_000_000 microseconds)
  Timer1.initialize(1000000);
  Timer1.attachInterrupt( light_next );
}

void loop() {
  if (!in_cycle) {
    if (pressed == 1) {
      button_pressed();
    } else  if (digitalRead(IR) == HIGH) {
      motion_detected();
    }
  }
}
