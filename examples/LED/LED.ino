#include"LED.h"

LED led(9);

void setup() {
     led.turnOn();
     delay(10);
     led.turnOff();
     delay(1000);
     led.blink(100,900);
}

void loop() {
     led.update();
}
