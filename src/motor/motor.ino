// deze app laat een motor draaien
// author: Christophe VG <contact@christophe.vg>

#define MOTOR1_EN    D0      // dit controleert of de motor in gebruik is
#define MOTOR1_1A    A0      // dit controleert de draairichting
#define MOTOR1_2A    A1      // dit controleert de draairichting

#define MIN_SNELHEID   200      // dit is de minimale snelheid = ~3V (van 5V)
#define MAX_SNELHEID   255      // dit is de maximale snelheid = ~3.5V (van 5V)

void setup() {
  Serial.begin(9600);
  pinMode(MOTOR1_EN, OUTPUT);
  pinMode(MOTOR1_1A, OUTPUT);
  pinMode(MOTOR1_2A, OUTPUT);
}

void motor_update(int16_t snelheid) {
  Serial.println(snelheid);
  // houd snelheid binnen grenzen
  if(abs(snelheid) < MIN_SNELHEID) { snelheid = 0; }
  if(abs(snelheid) > MAX_SNELHEID) {
    snelheid = MAX_SNELHEID * (snelheid/abs(snelheid));
  }

  // bepaal draairichting
  if(snelheid == 0) {
    // stop
    digitalWrite(MOTOR1_1A, LOW);
    digitalWrite(MOTOR1_2A, LOW);
  } else if(snelheid < 0) {
    // achterwaarts
    digitalWrite(MOTOR1_1A, HIGH);
    digitalWrite(MOTOR1_2A, LOW);
  } else {
    // voorwaarts
    digitalWrite(MOTOR1_1A, LOW);
    digitalWrite(MOTOR1_2A, HIGH);
  }
  // PWM
  analogWrite(MOTOR1_EN, abs(snelheid));
}

void loop() {
  motor_update(MAX_SNELHEID);
  delay(2000);
  motor_update(0);
  delay(2000);

  motor_update(MIN_SNELHEID);
  delay(2000);
  motor_update(0);
  delay(2000);
}
