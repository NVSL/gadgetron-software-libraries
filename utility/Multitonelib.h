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


#include <stdint.h>
#include <Arduino.h>

//Use the normal tone() noTone() functions if defined
//If not, uses the Tone.h external library 
#define NORMAL_TONE_FUNCTION

//Return during update() when a song beat happened
#define BEAT_SONG_UPDATE 1

//Return when the song stops
#define STOP_SONG_UPDATE 2


#ifndef NORMAL_TONE_FUNCTION
//Include an external library which can use multiple arduino timers
#include <Tone.h>
#endif

#include <math.h>

//Multiply this by the ticks to get milliseconds
//Equal to 2500/bpm for 96th ticks
//or 625/bpm for 96*4 ticks
#define TICKS_PER_BEAT 24
#define BEATS_PER_MINUTE 128
#define TICKS2MILLIS (60000 / (TICKS_PER_BEAT * BEATS_PER_MINUTE))
// #define TICKS2MILLIS 1


//Regular tone library can only do 1 tone at a time
#ifdef NORMAL_TONE_FUNCTION
  #define NUM_TONES 1
#else
  #define NUM_TONES 2
#endif


#define FCONST 440
//#define FCONST 330
#define ACONST 1.0594630943593
#define REST 0


class MultitonePlayer{

public:
  MultitonePlayer(const signed char *,const uint8_t *, int, int=0);
  void setup(int);
  uint8_t update();
  void start();
  
private:
  int _index;
  long _next_time;
  long _next_beat;
  int _pin;

#ifndef NORMAL_TONE_FUNCTION
  Tone tone_lib;
#endif

  int _transpose;
  int _num_notes;
  const signed char *pg_notes;
  const uint8_t *pg_note_lengths;
  static uint8_t _tone_count;

  signed char current_note();
  uint8_t current_length();

  void play_tone(int);
  void stop_tone();


};
