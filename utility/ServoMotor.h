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

#ifndef SERVO_WRAPPER
#define SERVO_WRAPPER

class GadgetManager;
#include <Servo.h>
#include "GadgetManager.h"

/**
 * This library controls servo motors attached to a microcontroller.
 * It provides support for both continuous rotation and postional rotation 
 * servos. By calling \p rotate(), you can specify the position you'd like your servo to rotate to.
 */
class ServoMotor {
  // The GadgetManager should be able to call block and enable but we want to
  // hide this from the user.
  friend class GadgetManager;
  public:
    /**
     * rief Constructor
     *
     * Set the \p pin that control the servo.
     *
     * If you use the sketch that came with your robot, you won't need call this.
     */
    ServoMotor( int pin );
    
    /**
     * rief Setup the servo
     *
     * Call this method in your \p setup() function.
     */
    void setup();
#ifndef GTRON_ARDUINO_SKIP
    /**
     * Attaches the servo to data pin. This is implicitly called in setup; 
     * but, must be called if you want to use the servo again after calling 
     * detach.
     */
    void attach();
    /**
     * Detaches the servo from its PWM timer. 
     */
    void detach();
#endif
    /**
     * rief Rotate!
     *
     * Sets the motor the the given angle \p degrees (0-180). 
     */
    void rotate( int degrees );
    
  private:
    // Detaches servo from timer and prevents user from accessing servo
    void block();
    // Allows servo to access timer but does not immediately re-claim it
    void enable();
    /*
     * Internal implementation of detach logic. 
 
     * Does not modify state bits 

     * For future Gadgetron Developers: 

     * The Arduino Servo library on which this function depends on doesn't 
 
     * fully function. It seems to disable the PWM timer the servo took up 
 
     * after it detaches. The solution right now is hardcoded into this 

     * but is specically tailored to the ATMega328. Whether this function 

     * works on other processors is unknown.
     */
    void _detach();

    // The Arduino Library Servo
    Servo servo;
    // Inside the Gadget Manager, every servo is a node in a
    // linked list of servos
    ServoMotor * next;
    // Data pin
    int pin;

    // State Bit Vector
    // Uses state definitions from GadgetManager
    unsigned char state;
};


#endif
