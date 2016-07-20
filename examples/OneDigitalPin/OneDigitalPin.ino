#include "Breakoutpins.h"

OneDigitalPin onePin = OneDigitalPin(8);

void setup() {
 
}

void loop() {
  onePin.write(HIGH);
  delay(1000);
  onePin.write(LOW);
  delay(1000);
}
