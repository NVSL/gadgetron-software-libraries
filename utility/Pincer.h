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

#ifndef PINCER_INCLUDED
#define PINCER_INCLUDED

#include <Arduino.h>
#include "ServoMotor.h"
#define PINCER_OPEN 1
#define PINCER_CLOSED  0

/**
 * Grab things, pinch things, carry things!
 *
 * If your gripper doesn't open or close all the way and/or makes grinding or
 * clicking noise, try calling \p setOpen() and/or \p setClose() in your \p
 * setup() function to adjust how it opens and closes.
 */

class Pincer
{
     //states
     uint8_t pin;
     uint8_t state;
     ServoMotor * srv;

     int MAX_ANGLE = 84;
     int MIN_ANGLE = 40;

public:
     /**									
      * rief Constructor
      *
      * Set the pin that control the gripper and open the gripper.
      *
      * If you use the sketch that came with your robot, you won't need call this.
      */
     Pincer(uint8_t pin);
     /**
      * rief Setup the gripper
      *
      * Call this method in your \p setup() function.
      */
     void setup();

     /**
      * rief Toggle
      *
      * If it's open, close it.  And vice versa.
      */
     void toggle();

     /**
      * rief Open!
      * 
      * Open all the way!
      */
     void open();

     /**
      * rief Open (with finesse)
      * 
      * \p angle tells how far to open the gripper.  \p angel needs to be between the
      * minimum and maximum angle.  The defaults for these are 40 (closed) and
      * 84 (open).
      */
     void open(int angle);

     /**
      * rief Grab!
      * 
      * Close the gripper.
      */
     void close();

     /**
      * rief Adjust open angle
      *
      * Adjust the angle that corresponds to opening the pincer.  The default
      * is 84.  If that doesn't open your pincer properly, experiment to find a
      * good setting.
      */
     void setOpen(int angle);

     /**
      * rief Adjust closed angle
      *
      * Adjust the angle that corresponds to closing the pincer.  The default
      * is 40.  If that doesn't close your pincer properly, experiment to find
      * a good setting.
      */
     void setClose(int angle);
     
#ifndef GTRON_ARDUINO_SKIP
     void onAndOff(int time, int times);
     void changeState();
     bool isOpen();
#endif
     
};

#endif
