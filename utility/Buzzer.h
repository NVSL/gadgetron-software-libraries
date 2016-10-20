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

#include <Arduino.h>
#include "NoteFrequencyTable.h"

/** 
 * This library allows your design to control a Piezo Buzzer to play simple 
 * tones. The library  is only able to play a tone from one buzzer at a time. 
 *
 * A note frequency table (NoteFrequencyTable.h) is bundled with this library
 * to make it easier to play musical notes from this library. 
 *
 * Example: 
 * 
 *   \p playNote(NOTE_A4, 200) 
 *
 * will play A at its 4th octave for 200 milliseconds
 */
class Buzzer {
  uint8_t pin;
  public:
    /** 
     * rief Constructor
     *
     * Creates a variable of type Buzzer. The \pin parameter is the hardware pin 
     * connecting the Buzzer to the microcontroller.
     *
     * If you use the sketch that came with your robot, you won't need call this.
     */ 
    Buzzer(uint8_t pin); 

    /**
     * rief Play a tone forever
     *
     * Plays the given frequency from the buzzer until you call \p turnOff().
     */
    void playNote( int frequency );

    /**
     * rief Play a tone for a while
     *
     * Plays the given \p frequency from the buzzer for \p noteLength milliseconds.
     */
    void playNote( int frequency, int noteLength );

    /** 
     * rief Turn off the buzzer
     */
    void turnOff();


#ifndef GTRON_ARDUINO_SKIP
    
    /** A placeholder setup function that currently doesn't do anything */
    void setup();
#endif
};
#endif
