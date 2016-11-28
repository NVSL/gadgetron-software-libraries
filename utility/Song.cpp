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

#include "Song.h"
#include "SongData.h"
Song::Song( Buzzer & buzzer ) {
  _buzzer = &buzzer;
}
void Song::playNextNote() {
  if( songIndex < LENGTH) {
	 // Calculate length in milliseconds
     int length =  (signed char)pgm_read_byte_near(noteLength + songIndex);
     length *= (2500/TEMPO);
     int semitoneValue = (signed char)pgm_read_byte_near(notes + songIndex);
     if( semitoneValue != REST ) {
		// Calculate frequency
	   _buzzer->playSemitone(semitoneValue, length);
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
