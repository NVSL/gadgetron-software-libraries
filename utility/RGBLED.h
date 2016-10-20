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

#ifndef RGBLED_H
#define RGBLED_H

#include <Arduino.h>

class RGBLED
{
  public:
     /**
      * rief Constructor
      *
      * By default, the LED is off, but you can set the color with \p red, \p green, and \p blue.
      *
      * If you use the sketch that came with your robot, you won't need call this.
      */
     RGBLED(int red = 0, int green = 0, int blue = 0, bool common_anode=true);

     /**
      * rief Setup the LED
      *
      * Call this function once in your setup() function.  Without it, the LED
      * won't work properly.
      */
     void setup();


#ifndef GTRON_ARDUINO_SKIP     
     void update();
#endif
     
     /**
      * rief Set the LED's color.
      *
      * The \p red, \p green, and \p blue parameter let you set the red, green, and blue levels.  0 = off, 255 = maximum brigtness.
      */
     void set(int red, int green, int blue);

     /**
      * rief Fade to a new color.
      *
      * Fade from the current color to a new color specified by \p red, \p
      * green, and \p blue.  The transition will take \p step steps, and each
      * step will take \p period milliseconds.
      *
      * This function will not return until the fade is complete.
      */
     void fade(int red, int green, int blue, int step, int period);

     
 private: 
     // pins for the colors
     const int red_pin, green_pin, blue_pin;
     
     // variable used to save current color
     int prev_red, prev_green, prev_blue;
     
     // cathode default is dark, anode is bright 
     const bool common_anode;

};

#endif
