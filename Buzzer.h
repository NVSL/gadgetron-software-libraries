#ifndef BUZZER_H
#define BUZZER_H

#include <Arduino.h>
#include "NoteFrequencyTable.h"

/** 
 * This library allows your design to control a Piezo Buzzer to play simple 
 * sounds. The sounds are square waves with a specifable frequency. The library 
 * is only able to play a tone from one buzzer at a time. 
 * A note frequency table (NoteFrequencyTable.h) is bundled with this library
 * to make it easier to play musical notes from this library. \n
 * Example: 
 * playNote(NOTE_A4, 200) will play A at its 4th octave for 200 milliseconds \n
 * Disclaimer: This library simply provides a thin wrapper layer around the 
 * exisiting Arduino Tone library accomidate a more object oriented approach to
 * controlling piezo buzzers.
 */
class Buzzer {
  uint8_t pin;
  public:
    /** Creates a variable of type LED. The pin parameter is the hardware pin 
     * connecting the Buzzer to the microcontroller
     */ 
    Buzzer(uint8_t pin); 
    /** Plays the given frequency from the buzzer until turnOff is called */
    void playNote( int frequency );
    /** Plays the given frequency from the buzzer for noteLength milliseconds */
    void playNote( int frequency, int noteLength );
    /** Stops the buzzer from playing any sounds */
    void turnOff();
    /** A placeholder setup function that currently doesn't do anything */
    void setup();
};
#endif
