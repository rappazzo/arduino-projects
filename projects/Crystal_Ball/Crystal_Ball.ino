#include <LiquidCrystal.h>

const int SWITCH = 6;
const int RS = 12;
const int ENABLE = 11;
const int D4 = 2;
const int D5 = 3;
const int D6 = 4;
const int D7 = 5;

int switchState = 0;
int prevSwitch = 0;
const char* REPLIES[] = {
  "Yes", "Most Likely", "Certainly", "Outlook good",
  "Unsure", "Ask again", "Doubtful", "No"
};
//https://lastminuteengineers.com/arduino-1602-character-lcd-tutorial/
LiquidCrystal lcd(RS, ENABLE, D4, D5, D6, D7);

const byte crystal_ball_ch[8] = {
  0b00100,
  0b01010,
  0b10001,
  0b10001,
  0b01010,
  0b00100,
  0b01110,
  0b11111
};

void setup() {
  lcd.begin(16, 2);
  pinMode(SWITCH, INPUT);
  lcd.createChar(0, crystal_ball_ch);
  lcd.print("Ask the");
  lcd.setCursor(0, 1);
  lcd.print("Crystal Ball ");
  lcd.write(byte(0)); //crystal ball character
}

void loop() {
  switchState = digitalRead(SWITCH);
  if (switchState != prevSwitch) {
    prevSwitch = switchState;
    if (switchState == LOW) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("The ball says:");
      lcd.setCursor(0, 1);
      int reply = random(8);
      lcd.print(REPLIES[reply]);
    }
  }
}
