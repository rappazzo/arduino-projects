
int notes[] = {262, 294, 330, 349};


void setup() {
  Serial.begin(9600);
}

void loop() {
  int keyVal = analogRead(A0);
  Serial.println(keyVal);

  if (keyVal > 900) {
    tone(8, notes[0]);
  } else if (keyVal >= 820 && keyVal <= 900) {
    tone(8, notes[1]); 
  } else if (keyVal >= 450 && keyVal <= 460) {
    tone(8, notes[2]); 
  } else if (keyVal >= 5 && keyVal <= 10) {
    tone(8, notes[3]); 
  } else {
    noTone(8);
  }

}
