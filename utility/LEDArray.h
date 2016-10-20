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

class LEDArray : public Adafruit_8x8matrix
{
    //states
    int rotation;

    public:
     /**
      * rief Constructor
      *
      * If you use the sketch that came with your robot, you won't need call this.
      */
    LEDArray();
#ifndef GTRON_ARDUINO_SKIP
    /** Constructor to make the LED Array.*/
    LEDArray(int dummyPin, int dummyPin2);
#endif
    
  /**
   * rief Setup the display
   *
   * Call this function once in your setup() function. 
   */
    void setup();
    /**
     * rief Clear the display.
     */
    void clear();
     /**
      * rief Draw a pixel
      *
      * Turn on the pixel at location \p x, \p y.  If \p color == 0, turn it off. Otherwise turn it on.
      */
    void drawPix(int x, int y);

     /**
      * rief Draw a line
      *
      * Start at (\p x0, \p y0), and draw a line to (\p x1, \p y1).  If \p color == 1, turn the pixels on.  Otherwise, turn them off.
      */

     void drawLine(int x1, int y1, int x2, int y2);
     /**
      * rief Draw an hollow rectangle
      *
      * Start at (\p x0, \p y0), and draw a hollow rectangle \p w pixels wide
      * and \p h pixels wide.  
      *
      */
    void drawRec(int x1, int y1, int x2, int y2);
     /**
      * rief Draw a filled rectangle
      *
      * Start at (\p x0, \p y0), and draw a filled rectangle \p w pixels wide
      * and \p h pixels wide.  
      *
      */
    void fillRec(int x1, int y1, int x2, int y2);

     /** 
      * rief Draw a hollow circle.
      *
      * Draw it at (\p x, \p y) with radius \p r.
      *
      */
    void drawCircle(int x, int y, int r);

     /** 
      * rief Draw a filled circle.
      *
      * Draw it at (\p x, \p y) with radius \p r.
      *
      */
    void fillCircle(int x, int y, int r);


     /** rief Print some text.
      *
      * Prints text to the display. If it's too long, it will scroll.
      */
#ifdef ARDUINO
     void printText(String text);
#else
     void printText(std::string text);
#endif
    

     /** rief Set brightness
     *
     * Set the brighness of the display: 0 = min, 15 = max 
     */
    void setBrightness(int level);

    /** rief Displays a happy face */
    void drawHappyFace();
    /** rief Displays a neutral face */
    void drawNeutralFace();
    /** rief Displays a sad face */
    void drawSadFace();
    
    /** rief Rotate the display clockwise
     *
     * Rotate the display 90 degrees clockwise. 
     */
    void turnClockwise();
    /** rief Rotate the display counter-clockwise
     *
     * Rotate the display 90 degrees clockwise. 
     */
    void turnCounterClockwise();
     /** rief Ignore this function.
      *
      */
     void writeDisplay(void){
	  Adafruit_LEDBackpack::writeDisplay();
     };
#ifndef GTRON_ARDUINO_SKIP

    /* Blinks the LEDs at a specified rate from 0 - 3 with 0 at off */
    void blink(int rate);
#endif


    private:
    const int LEFT = 0;
    const int UP = 1;
    const int RIGHT = 2;
    const int DOWN = 3;
};

#endif
