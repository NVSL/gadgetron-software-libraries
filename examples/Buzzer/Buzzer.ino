#include "Gadgetron.h"

Buzzer buzzer(9);

void setup() {
     buzzer.turnOn();
     delay(10);
     buzzer.turnOff();
     delay(1000);
     buzzer.blink(100,900);
}

void loop() {
     buzzer.update();
}
