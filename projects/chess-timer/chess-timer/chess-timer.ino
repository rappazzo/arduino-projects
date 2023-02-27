
unsigned long duration[2] = {0l, 0l};
unsigned long cur_mark = 0;

volatile int pressed = 0;

const int BUTTON_A = 2;
const int BUTTON_B = 3;
const int OFFSET = BUTTON_A;
int lastPressed = 0;

void set_buttonA_pressed() {
  pressed = BUTTON_A;
}
void set_buttonB_pressed() {
  pressed = BUTTON_B;
}

void setup() {
  pinMode(BUTTON_A, INPUT);
  pinMode(BUTTON_B, INPUT);
  attachInterrupt(digitalPinToInterrupt(BUTTON_A), set_buttonA_pressed, FALLING);
  attachInterrupt(digitalPinToInterrupt(BUTTON_B), set_buttonB_pressed, FALLING);
  
  Serial.begin(9600);
  Serial.println("Ready");
}

void do_pressed(int button) {
  int index = button - OFFSET;
  unsigned long now = millis();
  duration[index] += now - cur_mark;
  Serial.print(button == BUTTON_A ? "A" : "B");
  Serial.print(": ");
  Serial.print(duration[index] / 1000);
  Serial.print(".");
  Serial.print(duration[index] % 1000);
  Serial.print("s\n");
  cur_mark = now;
  lastPressed = button;
}

void loop() {
  if (pressed > 0) {
    if (cur_mark == 0) {
      Serial.print("Starting ");
      Serial.println(pressed == BUTTON_B ? "A" : "B");
      lastPressed = pressed;
      // The first button press starts the clock
      cur_mark = millis();
      pressed = 0;
    }
  }
  if (pressed == BUTTON_A) {
    if (lastPressed == BUTTON_B) {
      do_pressed(BUTTON_A);
    }
    pressed = 0;
  } else if (pressed == BUTTON_B) {
    if (lastPressed == BUTTON_A) {
      do_pressed(BUTTON_B);
    }
    pressed = 0;
  }
}
