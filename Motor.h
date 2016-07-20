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
 * This library enables a microcontroller to control motors. More specifically,
 * it controls a Sparkfun Motor Driver TB6612FNG which may control up to two 
 * motors. Motor drivers enable motors to drive both clockwise and 
 * counter-clockwise from the same circuit. From this library, a 
 * microcontroller may command its wheels to move foward, backwards, and to 
 * rotate the overall robot's orientation. The library can support any number 
 * of motor drivers.
 */
class Motor
{
   public:
    /**
	   * This is the constructor to make your motor.
	   * The arguments are the various pins that your motor connects to on its 
	   * board.
	   */
      Motor( uint8_t STBY, uint8_t PWMA, uint8_t AIN1, uint8_t AIN2, 
             uint8_t PWMB, uint8_t BIN1, uint8_t BIN2); 
	  /**
	   * Move the motors forward at full speed
	   */
      void forward();
	  /**
	   * Move the motors forward at a definable speed. \n
	   * Valid input range is 0 (Slowest Speed/Stopped) to 255 (Fastest Speed)
	   */
      void forward(uint8_t speed);
    /**
     * Accelerates the motors forward. \n 
     * startSpeed specifies the starting speed of the motors. \n
     * endSpeed specifies the value which we want our final speed to be. \n
     * rate specifies the rate at which startSpeed approaches endSpeed. \n
     * That is, the function calls forward(speed), delay(rate) \n
     */
      void accelerateForward( uint8_t startSpeed, uint8_t endSpeed, int rate );
    /**
     * Accelerates the motors backwards. \n 
     * startSpeed specifies the starting speed of the motors. \n
     * endSpeed specifies the value which we want our final speed to be. \n
     * rate specifies the rate at which startSpeed approaches endSpeed. \n
     * That is, the function calls backward(speed), delay(rate) \n
     */

      void accelerateBackward( uint8_t startSpeed, uint8_t endSpeed, int rate );
	  /**
	   * Move the motors backwards at full speed
	   */
      void backward();
	  /**
	   * Move the motors backwards at a definable speed.\n
	   * Valid input ranges 0 (Slowest Speed/Stopped) to 255 (Fastest Speed)
	   */
      void backward(uint8_t speed);
	  /**
	   * Move the motors to spin a gadget full speed to the left
	   */
      void spinLeft();
	  /**
	   * Move the motors to spin a gadget at a definable speed to the left.\n
	   * Valid input ranges from 0 (Slowest Speed/Stopped) to 255 (Fastest Speed)
	   */
      void spinLeft(uint8_t speed);
	   /**
	   * Move the motors to spin a gadget full speed to the right
	   */
      void spinRight();
	  /**
	   * Move the motors to spin a gadget at a definable speed to the right.\n
	   * Valid input ranges from 0 (Slowest Speed/Stopped) to 255 (Fastest Speed)
	   */
      void spinRight(uint8_t speed );
	  /**
	   * Move the motors forward while drifting to the right at top speed.\n
     * The left motor will move at half the speed of the right motor.
	   */
      void forwardAndRight();
	  /**
	   * Move the motors forward while drifting to the right at a definable \n 
	   * speed. The left motor will move at ratio * speed of the right motor.
	   */
      void forwardAndRight(uint8_t speed, float ratio);
	  /**
	   * Move the motors forward while drifting to the left at top speed.\n
     * The right motor will move at half the speed of the right motor.
	   */
      void forwardAndLeft();
	  /**
	   * Move the motors forward while drifting to the left at a definable \n 
	   * speed. The right motor will move at ratio * speed of the left motor.
	   */
      void forwardAndLeft(uint8_t speed, float ratio);
	  /**
	   * Sets the motors up to run. This method must be called before use!
	   */
      void setup();
	  /**
	   * Sends the stop signal to the motors
	   */
      void stop();
	  /**
	   * Sends the stop signal to the motors and lowers movement pins
	   */
      void brake();
	  /**
	   * Returns true if the motors are running, else false
	   */
      bool isMoving();
	  /**
	   * Changes spinLeft to spinRight and spinRight to spinLeft
	   */
      unsigned char swapDirections();
	  /**
	   * Changes forward to backward and backward to forward
	   */
      void changePolarity();
      

      void move(uint8_t motor, uint8_t speed, uint8_t direction);
     /**
      * Prevents the motor pins from doing anything
      */
      void disable();   
  private:
      uint8_t STBY, PWMA, AIN1, AIN2, PWMB, BIN1, BIN2;
      void _moveBoth( uint8_t speed, uint8_t polarity );
      int polarity;
      bool _isMoving;
      void accelerate( uint8_t startSpeed, uint8_t endSpeed, int rate, void (Motor::*)(uint8_t i) );
      void claimPins();
      unsigned char state = 0;


      //Deactivates all pins associated with the motor
      //No pinMode, no digitalWrites, no analogWrites
      //For serial debugging when there are pin conflicts

};
#endif
