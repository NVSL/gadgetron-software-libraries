#include "Breakoutpins.h"

int value;
OneAdcPin oneAdcPin = OneAdcPin(A0);

void setup() {
  Serial.begin(9600);
  // Initialize one adc pin in Analog 0
  oneAdcPin.setup();
}

void loop() {
  value = oneAdcPin.read();
  Serial.println(value);
  delay(1000);
}
