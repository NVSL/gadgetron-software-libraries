#include "Breakoutpins.h"


FourDigitalPin fourPin = FourDigitalPin(8, 9, 10, 11);

void setup() {
  
}

void loop() {
  fourPin.writeOne(HIGH);
  fourPin.writeTwo(HIGH);
  fourPin.writeThree(HIGH);
  fourPin.writeFour(HIGH);
  delay(1000);
  fourPin.writeOne(LOW);
  fourPin.writeTwo(LOW);
  fourPin.writeThree(LOW);
  fourPin.writeFour(LOW);
  delay(1000);
}
