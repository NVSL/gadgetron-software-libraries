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

#include "GadgetManager.h"

GadgetManager * GadgetManager::singleton = new GadgetManager();

void GadgetManager::registerServo( ServoMotor * servo ) {
    ServoMotor * oldHead = singleton->servoList;
    singleton->servoList = servo;
    servo->next = oldHead;
}

void GadgetManager::freePins(int pins[], int number ) {
    modifyPins( pins, number, true );
}

void GadgetManager::reenablePins(int pins[], int number ) {
    modifyPins( pins, number, false);
}

void GadgetManager::modifyPins(int pins[], int number, bool shouldFree ) {
    for( int i = 0; i < number; i++ ) {
        switch( pins[i] ) {
            // ServoPins
            case 9:
              modifyServo( shouldFree) ;
              break;
            case 10:
              modifyServo( shouldFree) ;
              break;
        }
    }
}

void GadgetManager::modifyServo(bool shouldBlock) {
    ServoMotor * servo = singleton->servoList;
    // If the servo exists and
    // If we are trying to block our servos and
    // If our servos are already blocked
    // Then exit the function
    if( servo != 0 && shouldBlock && (servo->state & BLOCKED)) return; 
    while( servo != 0 ) {
        shouldBlock ?
        servo->block()  :
        servo->enable() ;
        servo = servo->next;
    }
}
