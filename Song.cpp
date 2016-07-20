#include "Song.h"
Song::Song( Buzzer & buzzer ) {
  _buzzer = &buzzer;
}
void Song::playNextNote() {
  if( songIndex < LENGTH) {
	  // Calculate length in milliseconds
     int length = noteLength[songIndex] * (2500/TEMPO);
     if( notes[songIndex] != REST ) {
		// Calculate frequency
	   int freq = notes[songIndex];
	   freq = (int)(FCONST * pow(ACONST, freq));
       _buzzer->playNote( freq, (int)length );
     }
     else {
       _buzzer->turnOff();
     }
     delay((int)length);
     songIndex++;
  }
}
void Song::restartSong() {
  songIndex = 0;
}
void Song::playWholeSong() {
  while( songIndex < LENGTH ) {
    playNextNote();
  }
}

int Song::getIndex() { return songIndex; }
void Song::setIndex(int i) { songIndex = i; }
int Song::getLength() { return LENGTH; }
