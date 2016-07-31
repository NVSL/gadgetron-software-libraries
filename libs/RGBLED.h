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

#ifndef RGBLED_H
#define RGBLED_H

#include <Arduino.h>

class RGBLED
{
  public:
     RGBLED(int red, int green, int blue, bool common_anode=true);
     void set(int red, int green, int blue);
     void fade(int red, int green, int blue, int step, int period);
     void setup();
     void loop();
     
 private: 
     // pins for the colors
     const int red_pin, green_pin, blue_pin;
     
     // variable used to save current color
     int prev_red, prev_green, prev_blue;
     
     // cathode default is dark, anode is bright 
     const bool common_anode;

};

#endif

