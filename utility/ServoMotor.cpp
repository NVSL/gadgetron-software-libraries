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

#include "ServoMotor.h"
#include <Servo.h>


ServoMotor::ServoMotor( int pin ) {
  this->pin = pin;
  this->state = 0;
  this->next = 0;
}

void ServoMotor::setup() {
  this->state |= HAS_SETUP;
  this->attach();
  GadgetManager::registerServo( this );
}

void ServoMotor::attach() {
  this->state |= ATTACHED;
  if( IS_BLOCKED ) return;
  this->servo.attach( pin );
}

void ServoMotor::detach() {
  this->state &= (~ATTACHED);
  this->_detach();
}
void ServoMotor::_detach() {
  this->servo.detach();
  TCCR1B=0;
  TCCR1B=_BV(CS11);
  TCCR1B=_BV(CS10);
  TCCR1A=_BV(WGM10);
  TIMSK1=0;
}

void ServoMotor::rotate( int degrees ) {
  if( !IS_BLOCKED && ( state&ATTACHED ) && !servo.attached() )
    this->servo.attach( pin );
  this->servo.write( degrees );
}

void ServoMotor::block() {
  this->state |= BLOCKED;
  this->_detach();
}

void ServoMotor::enable() {
  this->state &= (~BLOCKED);
}
