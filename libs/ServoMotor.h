#ifndef SERVO_WRAPPER
#define SERVO_WRAPPER

class GadgetManager;
#include <Servo.h>
#include "GadgetManager.h"

/**
 * This library controls servo motors attached to a microcontroller.
 * It provides support for both continuous rotation and postional rotation 
 * servos. By calling rotate, you can specify how you want the servo to move.
 * The ServoMotor library supports up to 12 servo motors on most Arduino 
 * boards. The class wraps the Arduino Servo library to be compatible with the \n
 * Gadgetron tool-chain. 
 */
class ServoMotor {
  // The GadgetManager should be able to call block and enable but we want to
  // hide this from the user.
  friend class GadgetManager;
  public:
    /**
     * This is the constructor to make your ServoMotor. \n
     * The pin parameter is the data pin \n
     */
    ServoMotor( int pin );
	  /**
	   * Sets the servo up to run. This method must be called before use!
	   */
    void setup();
    /**
     * Attaches the servo to data pin. This is implicitly called in setup; \n
     * but, must be called if you want to use the servo again after calling \n
     * detach.
     */
    void attach();
    /**
     * Detaches the servo from its PWM timer. 
     */
    void detach();
    /**
     * Rotates the servo from its initial position to degrees. 
     */
    void rotate( int degrees );
  private:
    // Detaches servo from timer and prevents user from accessing servo
    void block();
    // Allows servo to access timer but does not immediately re-claim it
    void enable();
    /*
     * Internal implementation of detach logic. \n 
     * Does not modify state bits \n
     * For future Gadgetron Developers: \n
     * The Arduino Servo library on which this function depends on doesn't \n 
     * fully function. It seems to disable the PWM timer the servo took up \n 
     * after it detaches. The solution right now is hardcoded into this \n
     * but is specically tailored to the ATMega328. Whether this function \n
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
