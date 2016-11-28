/* Copyright (c) <2016> <mmg005@eng.ucsd.edu>
*
* Permission is hereby granted, free of charge, to any person obtaining a copy of
* this software and associated documentation files (the "Software"), to deal in 
* the Software without restriction, including without limitation the rights to use,
* copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the
* Software, and to permit persons to whom the Software is furnished to do so, 
* subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all 
* copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
* INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
* PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
* HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
* OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE 
* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "Buzzer.h"
/** Buzzer constructor. */ 
Buzzer::Buzzer( uint8_t pin ) { 
  this->pin = pin;
  pinMode( pin, OUTPUT);
}  
/** Plays the given frequency off the buzzer until turnOff is called */
void Buzzer::playNote( int frequency ) {
  tone(pin, frequency);
}
/** Plays the given frequency off the buzzer for noteLength milliseconds */
void Buzzer::playNote( int frequency, int noteLength ) {
  tone(pin, frequency, noteLength);
}
/** Stops the buzzer from playing any sounds */
void Buzzer::turnOff() {
  noTone(pin);
}

void Buzzer::playSemitone(int semitoneOffset, int noteLength)
{
	   int freq = (int)(FCONST * pow(ACONST, semitoneOffset));
       playNote( freq, noteLength);
}

/** A dummy setup function that doesn't actually do anything */
void Buzzer::setup() {}
