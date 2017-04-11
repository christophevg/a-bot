# Keypad

Dit is de basis opstelling voor het uitlezen van het keypad.

## Wat moet je bouwen?

De encoder wordt aangesloten met drie draden: 2 daarvan dienen voor de stroomvoorziening en de derde geeft een signaal terug dat aangeeft welke knop ingeduwd wordt.

Volgens de documentatie van het keypad, werkt dit op 5V. De Photon wordt wel gevoed met 5V, maar werkt voor de rest hoofdzakelijk op 3.3V. Als we naar de [samenstelling](https://iprototype.nl/docs/gravity-keypad-schema.pdf) van het keypad kijken, zien we dat de knoppen met verschillende weerstanden zorgen voor verschillende spanningen over de uitgaande, derde draad.

Voor dit voorbeeld, sluiten we het keypad dus aan op pinnen `3.3V`, `GND` en `A4`.

## Hoe werkt dit?

In de code bevindt zich 1 functie die de uitgaande spanning van het keypad leest en omzet tot een numerieke aanduiding voor de ingedrukte knop:

```c
#define KNOPPEN A4

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
```

## Hoe doe je dit werken op de Photon?

Vanuit de `src/` folder, geef je het commando `make`:

```bash
$ PROJECT=keypad make
*** Compileren en flashen van keypad
particle flash 2b002f001147333439313830 keypad
Including:
    keypad/keypad.ino
attempting to flash firmware to your device 2b002f001147333439313830
Flash device OK:  Update started
*** Start van console uitvoer. Beëindig met 'Ctrl+a k y'.
    Druk op een toets om verder te gaan...
```

Op de console toont de applicatie de knoppen die ingedrukt worden.
