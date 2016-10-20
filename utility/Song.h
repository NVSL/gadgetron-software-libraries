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

#ifndef SONG_HEADER
#define SONG_HEADER
#define REST -75
#define LENGTH 5
#define FCONST 261.626
#define ACONST 1.0594630943593
#define TEMPO 180
#include "Buzzer.h"
#include <math.h> 
#include <Arduino.h> 
class Song {
	Buzzer * _buzzer = NULL;
	int songIndex = 0;
	signed char notes[5]  { 0, 4, 7, 11, 12};
	signed char noteLength[5]  { 6, 6, 6, 6, 12};

	public:
	/**
	 * The constructor for a song takes a reference to a buzzer. The song
	 * can play off this buzzer.
	 */
	Song( Buzzer & buzzer );
	/**
	 * This plays the next note in the song. It will cause the Arduino to delay
	 * for the duration of the note. The song's internal index will also be 
	 * incremented by one.
	 */
	void playNextNote( );
	/**
	 * This resets the song's index to 0. 
	 */
	void restartSong( );
	/**
	 * This plays the entire song. The Arduino will delay for each note and 
	 * will prevent any input until the song finishes.
	 */
	void playWholeSong( );
	/**
	 * Returns the current index of the song
	 */
	int getIndex( );
	/**
	 * Sets the current index of the song
	 */
	void setIndex( int i );
	/**
	 * Returns the length or the number of notes for the song.
	 */
	int getLength( );
};
#endif
