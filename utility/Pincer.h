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

#ifndef PINCER_INCLUDED
#define PINCER_INCLUDED

#include <Arduino.h>
#include "ServoMotor.h"
#define PINCER_OPEN 1
#define PINCER_CLOSED  0
/**
 * Filename: Pincer.h
 * Description: Grab things, pinch things, destroy the world.
 */

class Pincer
{
    //states
    uint8_t pin;
    uint8_t state;
    ServoMotor * srv;

    public:
        /**
         * Constructor assigning the pin to variable and default is an open state
         */
        Pincer(uint8_t pin);
        void setup();
        void toggle();
        void open();
        void open(int angle);
        void close();
        void onAndOff(int time, int times);
        void changeState();
        void setOpen(int angle);
        void setClose(int angle);
        bool isOpen();
        void setMin(int min);
        void setMax(int max);

    private:
        int MAX_ANGLE = 84;
        int MIN_ANGLE = 40;
        int max_angle = 84;
        int min_angle = 40;
};

#endif
