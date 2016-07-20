#include "Buzzer.h"
Buzzer::Buzzer( uint8_t pin ) { 
  this->pin = pin;
  pinMode( pin, OUTPUT);
}  
void Buzzer::playNote( int frequency ) {
  tone(pin, frequency);
}
void Buzzer::playNote( int frequency, int noteLength ) {
  tone(pin, frequency, noteLength);
}
void Buzzer::turnOff() {
  noTone(pin);
}

void Buzzer::setup() {}
