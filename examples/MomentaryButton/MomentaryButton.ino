#include "Gadgetron.h"

MomentaryButton button(12);

void setup() {
    Serial.begin(57600);
}

void loop() {

  if (button.isPressed()) {
       Serial.println("Button pressed");
  }
  if (button.isReleased()) {
       Serial.println("Button released");
  }
  
  delay(10);
}
