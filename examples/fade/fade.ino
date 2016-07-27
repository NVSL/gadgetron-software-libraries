
#include <RGBLED.h>
// pins for led
RGBLED led(9, 10, 11);

void setup() {
  // put your setup code here, to run once:
  // default state is green
  led.set(0, 255, 0);

  // delay for 3 seconds
  delay (3000);

}

void loop() {
  // put your main code here, to run repeatedly:
  // Fades to red, blue, and back to red
  led.fade(255, 0, 0, 25, 2000);
  led.fade(0, 0, 255, 25, 2000);
  led.fade(255, 0, 0, 25, 2000);
}
