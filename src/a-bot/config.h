// configuratie van de a-bot
// author: Christophe VG <contact@christophe.vg>

#ifndef __CONFIG_H
#define __CONFIG_H

typedef struct {
  uint16_t en;
  uint16_t h1;
  uint16_t h2;
} motor_t;

// motoren 1 & 2
#define MOTOR1 (motor_t){ .en = A4, .h1 = A1, .h2 = A0 }
#define MOTOR2 (motor_t){ .en = D0, .h1 = D2, .h2 = D1 }

#define MIN_SNELHEID  160      // dit is de minimale snelheid = ~3V (van 5V)
#define MAX_SNELHEID  255      // dit is de maximale snelheid = ~3.5V (van 5V)

#define SNELHEID      MIN_SNELHEID

// encoders 1 & 2
#define ENCODER1      D3
#define ENCODER2      D5

#define STAPPEN_RECHT 53       // aantal stappen voor rechtdoor
#define STAPPEN_DRAAI 10       // aantal stappen voor kwart draai

// keypad
#define KNOPPEN       A5

// offline support
#define CONNECT       D4

#endif
