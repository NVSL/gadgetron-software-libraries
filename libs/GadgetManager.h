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

#ifndef GADGET_MANAGER
#define GADGET_MANAGER

class ServoMotor;
class Motor;
// These are state bits for any part
#define HAS_SETUP 1
#define ATTACHED 2
#define BLOCKED 0x80

// State Macros
#define IS_BLOCKED (state & BLOCKED) 


#include <Arduino.h>
#include "ServoMotor.h"

/**
 * Filename: GadgetManager.h \n 
 * Author: Michael Gonzalez \n
 * Description: This class managers critical resources in Gadgetron Robots.\n
 * Currently, its primary function is to allow the motor drivers to reclaim \n
 * PWM pins if servos have control over them. 
 */

class GadgetManager {
    friend class ServoMotor;
    friend class Motor;
    private:
        /*
         * Registers a servo with the GadgetManager.
         */
        static void registerServo( ServoMotor * servo );
        /*
         * Allows the calling class to use a list of pins. \n
         * pins is the list of pins to free \n
         * number is the number of pins in pins \n
         */
        static void freePins(int pins[], int number );
        /*
         * Allows the original holder of a pin to have access to it again \n
         * pins is the list of pins to restore \n
         * number is the number of pins in pins \n
         */
        static void reenablePins(int pins[], int number );
        // Only one GadgetManger should ever exist at a time! DO NOT MODIFY
        static GadgetManager * singleton;
        // Helper function to freePins and reenable pins
        static void modifyPins(int pins[], int number, bool shouldFree );
        // Can call block and disable on entire servo list
        // If should block is true,
        // Then this function calls block on the whole list
        // Else, this function calls enable on the whole list
        static void modifyServo(bool shouldBlock);
        ServoMotor * servoList = 0;
};


#endif
