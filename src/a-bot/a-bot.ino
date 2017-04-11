// dit is de applicatie voor de (hele) A-Bot
// author: Christophe VG <contact@christophe.vg>

#include "config.h"

void setup() {
  Serial.begin(9600);

  // motoren 1 & 2
  pinMode(MOTOR1.en, OUTPUT);
  pinMode(MOTOR1.h1, OUTPUT);
  pinMode(MOTOR1.h2, OUTPUT);

  pinMode(MOTOR2.en, OUTPUT);
  pinMode(MOTOR2.h1, OUTPUT);
  pinMode(MOTOR2.h2, OUTPUT);

  // encoders 1 & 2
  attachInterrupt(ENCODER1, encoder1_verandering, CHANGE);
  attachInterrupt(ENCODER2, encoder2_verandering, CHANGE);
}

void motor_update(motor_t motor, int16_t snelheid) {
  // houd snelheid binnen grenzen
  if(abs(snelheid) < MIN_SNELHEID) { snelheid = 0; }
  if(abs(snelheid) > MAX_SNELHEID) {
    snelheid = MAX_SNELHEID * (snelheid/abs(snelheid));
  }

  Serial.print(motor.en); Serial.print( " = " ); Serial.println(snelheid);

  // PWM
  analogWrite(motor.en, abs(snelheid));

  // bepaal draairichting
  if(snelheid == 0) {
    digitalWrite(motor.h1, HIGH);
    digitalWrite(motor.h2, HIGH);
    delay(50);
    // stop
    digitalWrite(motor.h1, LOW);
    digitalWrite(motor.h2, LOW);
  } else if(snelheid < 0) {
    // achterwaarts
    digitalWrite(motor.h1, HIGH);
    digitalWrite(motor.h2, LOW);
  } else {
    // voorwaarts
    digitalWrite(motor.h1, LOW);
    digitalWrite(motor.h2, HIGH);
  }
}

// encoders
volatile uint16_t stappen1 = 0;
volatile uint16_t stappen2 = 0;

void encoder1_verandering() {
  stappen1++;
}

void encoder2_verandering() {
  stappen2++;
}

// keypad
// s1    s2     s3      s4     s5
//   600    650    700     800    900
uint8_t lees_knoppen() {
  int invoer = 4095 - analogRead(KNOPPEN);
  if(invoer < 200) { return 0; }
  if(invoer < 300) { return 5; }
  if(invoer < 500) { return 4; }
  if(invoer < 645) { return 1; }
  if(invoer < 675) { return 3; }
  if(invoer < 800) { return 2; }
  return 0; // geen knop
}

// hulp functies

uint16_t doel1 = 0;
uint16_t doel2 = 0;

void vooruit() {
  stappen1 =  0;
  stappen2 =  0;
  doel1    = STAPPEN_RECHT;
  doel2    = STAPPEN_RECHT;
  motor_update(MOTOR1,  SNELHEID);
  motor_update(MOTOR2, -SNELHEID);
}

void links() {
  stappen1 =  0;
  stappen2 =  0;
  doel1    = STAPPEN_DRAAI;
  doel2    = STAPPEN_DRAAI;
  motor_update(MOTOR1,  SNELHEID);
  motor_update(MOTOR2,  SNELHEID);
}

void rechts() {
  stappen1 =  0;
  stappen2 =  0;
  doel1    = STAPPEN_DRAAI;
  doel2    = STAPPEN_DRAAI;
  motor_update(MOTOR1, -SNELHEID);
  motor_update(MOTOR2, -SNELHEID);
}

void achteruit() {
  stappen1 =  0;
  stappen2 =  0;
  doel1    = STAPPEN_RECHT;
  doel2    = STAPPEN_RECHT;
  motor_update(MOTOR1, -SNELHEID);
  motor_update(MOTOR2,  SNELHEID);
}

void stop() {
  stappen1 = 0;
  stappen2 = 0;
  doel1    = 0;
  doel2    = 0;
  motor_update(MOTOR1, 0);
  motor_update(MOTOR2, 0);
}

// bediening

uint8_t vorige_knop = 0;
bool rijden = false;

void loop() {
  if(rijden) {
    loop_rijden();
  } else {
    loop_stilstaan();
  }
  delay(100);
}

uint8_t programma[255];
uint8_t pc = 0;

void stap() {
  Serial.print("stap ");
  Serial.print(pc); Serial.print(" = "); Serial.println(programma[pc]);
  
  rijden = true;
  switch(programma[pc]) {
    case 4: vooruit();   break;
    case 3: rechts();    break;
    case 2: achteruit(); break;
    case 1: links();     break;
    case 5:
      pc = 0;
      rijden = false;
      break;
  }
}

void loop_rijden() {
  uint8_t knop = lees_knoppen();

  // manueel onderbreken van het rijden
  if(knop != vorige_knop) {
    Serial.println("STOP!");
    stop();         // van zodra een knop aangeraakt wordt, stoppen we
    if(knop == 0) { // als de knop los gelaten is, gaan we over naar stilstaan
      rijden = false;
    }
    vorige_knop = knop;
    return;
  }

  // rijden tot doel bereikt is
  if(doel1 > 0 && stappen1 >= doel1) { motor_update(MOTOR1, 0); doel1 = 0; }
  if(doel2 > 0 && stappen2 >= doel2) { motor_update(MOTOR2, 0); doel2 = 0; }
  
  // normaal einde van het rijden, volgende stap
  if(doel1 == 0 && doel2 == 0) {
    pc++;
    stap();
  }
}

void loop_stilstaan() {
  uint8_t knop = lees_knoppen();

  if(knop != vorige_knop) {
    if(knop == 0) { // pas als de knop losgelaten wordt, starten we
      Serial.print(pc); Serial.print(" = "); Serial.println(vorige_knop);
      programma[pc++] = vorige_knop;
      if( vorige_knop == 5 ) {
        Serial.println("start...");
        pc = 0;
        stap();
      }
    }
    vorige_knop = knop;
  }
}
