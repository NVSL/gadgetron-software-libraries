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

#ifndef BUZZER_H
#define BUZZER_H
#define FCONST 261.626
#define ACONST 1.0594630943593

#include <Arduino.h>
#include "NoteFrequencyTable.h"

/** Filename: Buzzer.h 

 *  Author: Michael Gonzalez 

 *  Description: This file provides a simple interface to control piezo buzzers 

 *               on Arduino projects. A note frequency lookup table is provided 

 *               to facilitate easy musical note entry. For example, a user 

 *               only has to pass NOTE_A4 to the playNote function to play the A 

 *               note at the 4th octave rather than having to specify 440 as 

 *               the frequency to play A4.
 */
class Buzzer {
  uint8_t pin;
  public:
    /** Buzzer constructor. */ 
    Buzzer(uint8_t pin); 
    /** Plays the given frequency off the buzzer until turnOff is called */
    void playNote( int frequency );
    /** Plays the given frequency off the buzzer for noteLength milliseconds */
    void playNote( int frequency, int noteLength );
	/** Plays the note with the semitone offset from middle C (C4) */
	void playSemitone(int semitoneOffset, int noteLength);
    /** Stops the buzzer from playing any sounds */
    void turnOff();
    /** A dummy setup function that doesn't actually do anything */
    void setup();
};
#endif
