int RED   = 9;
int GREEN = 11;
int BLUE  = 10;

int BUTTON = 2;

int RED_I   = 0;
int GREEN_I = 1;
int BLUE_I  = 2;

int color[] = {255,0,0};

int is_bounce() {
   static unsigned long last_interrupt_time = 0;
   unsigned long interrupt_time = millis();
   // If interrupts come faster than 200ms, assume it's a bounce and ignore
   if (interrupt_time - last_interrupt_time <= 200) {
     return 1;
   }
   last_interrupt_time = interrupt_time;
   return 0;
}

void printColor() {
  Serial.print("   COLOR - red: ");
  Serial.print(color[0]);
  Serial.print(", green: ");
  Serial.print(color[1]);
  Serial.print(", blue: ");
  Serial.print(color[2]);
  Serial.println();
}

void button_pressed() {
  if (is_bounce()) return;
  
  if (color[RED_I] > 0) {
    color[RED_I]   = 0;
    color[GREEN_I] = 255;
    color[BLUE_I]  = 0;
  } else if (color[GREEN_I] > 0) {
    color[RED_I]   = 0;
    color[GREEN_I] = 0;
    color[BLUE_I]  = 255;
  } else {
    color[RED_I]   = 255;
    color[GREEN_I] = 0;
    color[BLUE_I]  = 0;
  }
  printColor();
}

void setup() {
  Serial.begin(9600);
  pinMode(RED,    OUTPUT);
  pinMode(GREEN,  OUTPUT);
  pinMode(BLUE,   OUTPUT);
  
  pinMode(BUTTON, INPUT);
  attachInterrupt(digitalPinToInterrupt(BUTTON), button_pressed, RISING);

  printColor();
}

void loop() {
  analogWrite(RED, color[0]);
  analogWrite(GREEN, color[1]);
  analogWrite(BLUE, color[2]);

  delay(100);
}
