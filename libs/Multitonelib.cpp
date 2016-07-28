
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



