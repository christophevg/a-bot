// de eenvoudigste test om te controleren dat alles werkt
// dit laat de ingebouwde blauwe LED van de Photon blinken
// auteur: Christophe VG <contact@christophe.vg>

#define LED    D7      // dit is de standaard led die op pin D7 verbonden is

void setup() {
  // configureer de LED pin voor uitvoer
  pinMode(LED, OUTPUT);
}

void loop() {
  digitalWrite(LED, HIGH);   // zet LED pin hoog
  delay(1000);               // wacht voor 1000ms = 1 sec
  digitalWrite(LED, LOW);    // zet LED pin laag
  delay(1000);               // en wacht opnieuw 1 sec
}
