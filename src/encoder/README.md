# Encoder

Dit is de basis opstelling voor het uitlezen van een encoder.

## Wat moet je bouwen?

Dit voorbeeld bouwt voort op het voorbeeld voor de [motor](../motor/). Op de [wiki van DFRobot](https://www.dfrobot.com/wiki/index.php/Wheel_Encoders_for_DFRobot_3PA_and_4WD_Rovers_(SKU:SEN0038)) vind je informatie hoe je de encoder op de motor kan aansluiten.

De gebruikte motoren verschillen echter een beetje en vragen wat knutselwerk. De opstelling van het chassis laat echter toe om de encoder op de vertikale steunen te bevestigen nadat de motoren langs de andere kant van de steun bevestigd is.

(_foto's volgen_)

## Hoe werkt dit?

Een encoder bestaat uit een getand wieltje en een lichtsensor. Wanneer het wieltje met de as van de motor ronddraait zullen de tandjes het licht afwisselend doorlaten of tegenhouden.

De encoder vraagt een 5V voeding en geeft een digitaal signaal terug dat aangeeft of de encoder licht detecteert of niet. Zo kunnen we het aantal tandjes dat ronddraaien tellen.

## Hoe doe je dit werken op de Photon?

Vanuit de `src/` folder, geef je het commando `make`:

```bash
$ PROJECT=encoder make
*** Compileren en flashen van encoder
particle flash 2b002f001147333439313830 encoder
Including:
    encoder/encoder.ino
attempting to flash firmware to your device 2b002f001147333439313830
Flash device OK:  Update started
*** Start van console uitvoer. Beëindig met 'Ctrl+a k y'.
    Druk op een toets om verder te gaan...
```

Op de console toont de applicatie telkens het aantal stappen dat geteld werd gedurende 2 seconden.
