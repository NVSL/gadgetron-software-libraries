/* Copyright (c) <2016> <mmg005@eng.ucsd.edu >
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

#include "Multitonelib.h"

uint8_t MultitonePlayer::_tone_count = 0;

int note2freq(signed char note) {
  return (int)round(FCONST * pow(ACONST, (int)note - 69));
}


MultitonePlayer::MultitonePlayer(const signed char *notes,const uint8_t *lengths, int count, int transpose){
  _transpose = transpose;
  _num_notes = count;
  pg_notes = notes;
  pg_note_lengths = lengths;
}

void MultitonePlayer::start(){
  _next_time = millis();
  _next_beat = _next_time;
}

void MultitonePlayer::setup(int pin){

#ifndef NORMAL_TONE_FUNCTION
  if(_tone_count++ < 2){
    tone_lib.begin(pin);
  }
#endif

  _pin = pin;
  _next_time = millis();
  _index=0;
}

signed char MultitonePlayer::current_note(){
  return pgm_read_byte(pg_notes + _index);
}

uint8_t MultitonePlayer::current_length(){
  return pgm_read_byte(pg_note_lengths + _index);
}

uint8_t MultitonePlayer::update(){
  if(millis() >= _next_time){
    stop_tone();

    if(_index < _num_notes){
      if(current_note() != REST){
        play_tone(note2freq( current_note() + _transpose ));
      }

      _next_time += TICKS2MILLIS*current_length();
      _index++;
    }else{
      return STOP_SONG_UPDATE;
    }
  }

  if(millis() >= _next_beat){
    _next_beat += TICKS2MILLIS * TICKS_PER_BEAT;
    return BEAT_SONG_UPDATE;
  }

  return 0;
  
}


void MultitonePlayer::play_tone(int freq){
#ifdef NORMAL_TONE_FUNCTION
  tone(_pin, freq);
#else
  tone_lib.play(freq);
#endif
}


void MultitonePlayer::stop_tone(){
#ifdef NORMAL_TONE_FUNCTION
  noTone(_pin);
#else
  tone_lib.stop();
#endif
}



