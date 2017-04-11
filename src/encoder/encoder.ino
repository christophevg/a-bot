// deze app laat een motor draaien en telt via de encoder de stappen
// auteur: Christophe VG <contact@christophe.vg>

#define MOTOR1_EN    D0      // dit controleert of de motor in gebruik is
#define MOTOR1_1A    A0      // dit controleert de draairichting
#define MOTOR1_2A    A1      // dit controleert de draairichting

#define ENCODER      D2

void setup() {
  Serial.begin(9600);
  pinMode(MOTOR1_EN, OUTPUT);
  pinMode(MOTOR1_1A, OUTPUT);
  pinMode(MOTOR1_2A, OUTPUT);
  
  attachInterrupt(ENCODER, encoder_verandering, CHANGE);
}

void motor_start() {
  digitalWrite(MOTOR1_EN, HIGH);
  digitalWrite(MOTOR1_1A, HIGH);
  digitalWrite(MOTOR1_2A, LOW);
}

void motor_stop() {
  digitalWrite(MOTOR1_EN, LOW);
  digitalWrite(MOTOR1_1A, LOW);
  digitalWrite(MOTOR1_2A, LOW);
}

volatile uint16_t stappen = 0;

void encoder_verandering() {
  stappen++;
}

void loop() {
  stappen = 0;
  motor_start();
  delay(2000);
  motor_stop();
  Serial.println(stappen);

  delay(2000);
}
