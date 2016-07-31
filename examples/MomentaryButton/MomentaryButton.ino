#include "Gadgetron.h"

MomentaryButton button(12);

void setup() {
    Serial.begin(57600);
}

void loop() {

  if (button.buttonPressed()) {
       Serial.println("Button pressed");
  }
  if (button.buttonReleased()) {
       Serial.println("Button released");
  }
  
  if (button.buttonDown()) {
       Serial.println("Button is down");
  }
  
  delay(10);
}
