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

#include "Pincer.h"

Pincer::Pincer(uint8_t pin)
{
    this->pin = pin;
    state = PINCER_OPEN;
}

void Pincer::setup()
{
    srv = new ServoMotor(pin);
    srv ->setup();
}

void Pincer::changeState()
{
    if(state)
        state = PINCER_CLOSED;
    else
        state = PINCER_OPEN;
}

void Pincer::toggle()
{
    if(state)
        close();
    else
        open();
}

void Pincer::open()
{
    open(MIN_ANGLE);
}

void Pincer::open(int angle)
{
    state = PINCER_OPEN;
    if(angle >= MIN_ANGLE && angle <= MAX_ANGLE)
        srv->rotate(angle);
}

void Pincer::close()
{
    state = PINCER_CLOSED;
    srv->rotate(MAX_ANGLE);
}

void Pincer::onAndOff(int time, int times)
{
    for(int i = 0; i < times; i++)
    {
        toggle();
        delay(time);
    }
}

void Pincer::setOpen(int angle)
{
    MIN_ANGLE = angle;
}

void Pincer::setClose(int angle)
{
    MAX_ANGLE = angle;
}

bool Pincer::isOpen()
{
    return state == PINCER_OPEN;
}
