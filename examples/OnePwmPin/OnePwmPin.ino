#include "Breakoutpins.h"

OnePwmPin onePwmPin = OnePwmPinN(6);

void setup() {
  // Initialize one pwm pin in 6
  onePwmPin.setup();
  // Writes half duty cycle value on pin 6
  onePwmPin.write(128);
}

void loop() {
  
}
