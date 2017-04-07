#define KNOPPEN A4

void setup() {
  Serial.begin(9600);
}

uint8_t vorige_knop = 0;

void loop() {
  uint8_t knop = lees_knoppen();
  if(knop != vorige_knop) {
    if(knop > 0) {
      Serial.print("knop: ");
      Serial.println(knop);
    }
    vorige_knop = knop;
  }
  delay(100);
}

// s1    s2     s3      s4     s5
//   600    650    700     800    900
uint8_t lees_knoppen() {
  int invoer = 4095 - analogRead(KNOPPEN);
  // Serial.println(invoer);
  if(invoer < 200) { return 0; }
  if(invoer < 300) { return 5; }
  if(invoer < 500) { return 4; }
  if(invoer < 645) { return 1; }
  if(invoer < 675) { return 3; }
  if(invoer < 800) { return 2; }
  return 0; // geen knop
}
