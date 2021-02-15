int RED   = 9;
int GREEN = 11;
int BLUE  = 10;

int RED_I   = 0;
int GREEN_I = 1;
int BLUE_I  = 2;

int color[] = {0,0,0};
int i = 0;

void setup() {
  Serial.begin(9600);
  pinMode(GREEN,  OUTPUT);
  pinMode(RED,    OUTPUT);
  pinMode(BLUE,   OUTPUT);
}

void loop() {
  color[RED_I]   = ((i>>8) & 0xf) * 0x11;
  color[GREEN_I] = ((i>>4) & 0xf) * 0x11;
  color[BLUE_I]  = (i & 0xf) * 0x11;
  Serial.print("   COLOR - red: ");
  Serial.print(color[0]);
  Serial.print(", green: ");
  Serial.print(color[1]);
  Serial.print(", blue: ");
  Serial.print(color[2]);
  Serial.println();

  analogWrite(RED, color[0]);
  analogWrite(GREEN, color[1]);
  analogWrite(BLUE, color[2]);

  i++;
  if (i > 1<<12) {
    i = 0;
  }
  delay(100);
}
