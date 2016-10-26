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

#ifndef MOTOR_H
#define MOTOR_H

#ifdef ARDUINO
#include <Arduino.h>
#else
#include "arduPi.h"
#endif

class GadgetManager;
#include "GadgetManager.h"
#define MOTOR_PIN_ARRAY {STBY, PWMA, AIN1, AIN2, PWMB, BIN1, BIN2} 
#define MOTOR_PIN_C 7

#define POLARITY_BIT 2
#define DIRECTION_BIT 4
#define MOVING_BIT 8

#define MOTOR_A_ORIG 1
#define MOTOR_B_ORIG 0
#define MOTOR_A ( (state & DIRECTION_BIT) ? MOTOR_B_ORIG : MOTOR_A_ORIG )
#define MOTOR_B ( (state & DIRECTION_BIT) ? MOTOR_A_ORIG : MOTOR_B_ORIG )

/**
 * Drive your robot!  Forward, backward, turns, this you can do it all!  At different speeds!
 *
 * If your robot seems to respond backwards (e.g., forward is backward and/or
 * left is right), try calling \p swapDirections() and/or \p changePolarity().
 *
 * If you want more detailed control, checkout \p move().
 */
class Motor
{
 public:
     /**
      * rief Constructor
      *
      * The arguments are the various pins that your motor connects to on its 
      * board.
      *
      * If you use the sketch that came with your robot, you won't need call this.
      */
     Motor( uint8_t STBY, uint8_t PWMA, uint8_t AIN1, uint8_t AIN2, 
	    uint8_t PWMB, uint8_t BIN1, uint8_t BIN2); 

     /**
      * rief Setup the motors
      *
      * Call this method in your \p setup() function.
      */
     void setup();

     /**
      * rief Forward!
      *
      * Drive motors forward at given speed: 0 = stop, 255 = fastest (the default).
      */
     void forward(uint8_t speed =255);

     
     /**
      * rief Backward!
      *
      * Drive motors backward at given speed: 0 = stop, 255 = fastest (the default).
      */
     void backward(uint8_t speed = 255);

     /**
      * rief Spin left!
      *
      * Spin to the left at a given speed: 0 = stop, 255 = fastest (the default).
      */
     void spinLeft(uint8_t speed=255);
     
     /**
      * rief Spin right!
      *
      * Spin to the right at a given speed: 0 = stop, 255 = fastest (the default).
      */
     void spinRight(uint8_t speed =255);
     
     /**
      * rief Turn to the right
      *
      * Drive motors forward while turning to the right.  \p speed is the speed
      * of the left motor.  \p ratio sets the speed of the right motor relative
      * to the right.  
      *
      * The defaults are \p speed = 255 (top speed) and \p ratio
      * = 0.5 (left runs half as fast as the right).
      */
     void forwardAndRight(uint8_t speed=255, float ratio=0.5);
     
     /**
      * rief Turn to the left
      *
      * Drive motors forward while turning to the left.  \p speed is the speed
      * of the right motor.  \p ratio sets the speed of the left motor relative
      * to the right.  
      *
      * The defaults are \p speed = 255 (top speed) and \p ratio
      * = 0.5 (right runs half as fast as the right).
      */
     void forwardAndLeft(uint8_t speed=255, float ratio=0.5);
     
     /**
      * rief Stop
      *
      * Stops the motors.  The robot may coast for awhile.
      */
     void stop();
     
     /**
      * rief Stop!!!
      *
      * Apply the brakes and stop faster.
      */
     void brake();
     

     /**
      * rief Speedup forward
      *
      * Accelerates the motors over time.  
      * \p startSpeed is the starting speed of the motors, and
      * \p endSpeed is final speed.
      * \p accelerationTime specifies the time in milliseconds requied to reach \p endSpeed. 

      */
     void accelerateForward( uint8_t startSpeed, uint8_t endSpeed, long accelerationTime);

     /**
      * rief Speedup backward
      *
      * Accelerates the motors over time.  
      * \p startSpeed is the starting speed of the motors, and
      * \p endSpeed is final speed.
      * \p accelerationTime specifies the time in milliseconds requied to reach \p endSpeed. 

      */
     
     void accelerateBackward( uint8_t startSpeed, uint8_t endSpeed, long accelerationTime);
     
     /**
      * rief Am I moving?
      *
      * Returns true if the motors are running, else false
      */
     bool isMoving();
     
     /**
      * rief Swap left and right.
      *
      * Swap the meanings of left and right.  Call this in your \p setup() function if your robot is confused about its right and left.
      */
     unsigned char swapDirections();
     
     /**
      * rief Swap forward and backward
      *
      * Swopp the meanings of forward and backward.  Call this in your \p setup() function if your robot is confused about which is way is forward.
      */
     void changePolarity();

     /**
      * rief Detailed control
      *
      * Lower level motor control function.
      * If \p motor == 0, then control one motor.  If \p motor == 1, then control the other (you may need to experiment to see which is which).
      * \p speed sets the drive speed.
      * If \p direction == 0, then drive forward, otherwhile drive backward.
      */
     void move(uint8_t motor, uint8_t speed, uint8_t direction);

#ifndef GTRON_ARDUINO_SKIP
     /**
      * Prevents the motor pins from doing anything
      */
     void disable();   
#endif
 private:
     uint8_t STBY, PWMA, AIN1, AIN2, PWMB, BIN1, BIN2;
     void _moveBoth( uint8_t speed, uint8_t polarity );
     int polarity;
     bool _isMoving;
     void accelerate( uint8_t startSpeed, uint8_t endSpeed, long aTime, void (Motor::*)(uint8_t i) );
     void claimPins();
     unsigned char state = 0;


     //Deactivates all pins associated with the motor
     //No pinMode, no digitalWrites, no analogWrites
     //For serial debugging when there are pin conflicts

};
#endif
