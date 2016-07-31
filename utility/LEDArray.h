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

#ifndef LEDARRAY_INCLUDED
#define LEDARRAY_INCLUDED

#include <Arduino.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

/**
 * Filename: LED_Array.h
 * Description: Wraps the adafruit library package into an easier-to-use
 * class. Allows the user to light up a matrix of LEDs.
 */

//Pre-built matrix formations
static const uint8_t PROGMEM
smile_bmp[] =
{ B00111100,
    B01000010,
    B10100101,
    B10000001,
    B10100101,
    B10011001,
    B01000010,
    B00111100 },
    neutral_bmp[] =
{ B00111100,
    B01000010,
    B10100101,
    B10000001,
    B10111101,
    B10000001,
    B01000010,
    B00111100 },
    frown_bmp[] =
{ B00111100,
    B01000010,
    B10100101,
    B10000001,
    B10011001,
    B10100101,
    B01000010,
    B00111100 },
    crosshatch[] =
{ B10101010,
    B01010101,
    B10101010,
    B01010101,
    B10101010,
    B01010101,
    B10101010,
    B01010101
};

class LEDArray
{
    //states
    int rotation;
    Adafruit_8x8matrix matrix = Adafruit_8x8matrix();

    public:
    /** Constructor to make the LED Array.*/
    LEDArray();
    /** Constructor to make the LED Array.*/
    LEDArray(int dummyPin, int dummyPin2);
    /** Creates the matrix from included LEDBackpack library */
    void setup();
    /** Clears the matrix and displays a blank screen */
    void clear();
    /** Displays a happy face */
    void drawHappyFace();
    /** Displays a neutral face */
    void drawNeutralFace();
    /** Displays a sad face */
    void drawSadFace();
    /** Rotates so the bottom is on a new side, moving clockwise 1 side */
    void turnClockwise();
    /** Rotates so the bottom is on a new counter clockwise side */
    void turnCounterClockwise();
    /** Prints text as input by the user as a string */
    #ifdef ARDUINO
    void printText(String text);
    #else
    void printText(std::string text);
    #endif
    /** fills in a pixel and displays it */
    void drawPix(int x, int y);
    /* Draws a line given two points */
    void drawLine(int x1, int y1, int x2, int y2);
    /* Draws the border of a rectangle given two points */
    void drawRec(int x1, int y1, int x2, int y2);
    /* Draws and fills in a rectangle given two points */
    void fillRec(int x1, int y1, int x2, int y2);
    /* Draws a circle */
    void drawCircle(int x, int y, int r);
    /* Blinks the LEDs at a specified rate from 0 - 3 with 0 at off */
    void blink(int rate);
    /* Sets the brighness of the lights to a level 0 - 15 with 0 not off */
    void setBrightness(int level);

    private:
    const int LEFT = 0;
    const int UP = 1;
    const int RIGHT = 2;
    const int DOWN = 3;
};

#endif
