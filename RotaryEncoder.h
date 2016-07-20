#ifndef ROTARY_ENCODER
#define ROTARY_ENCODER
#include <Arduino.h> 
#include <PinChangeInt.h>   //Still need to #include in the main .ino code too
#include <MomentaryButton.h>
/**
 * This library allows your design to receive input from a rotary encoder. 
 * The rotary encoder can be used as both a knob and a button. 
 */
class RotaryEncoder {
	int pinA, pinB, currentPos, maxPos, pinButton;
	uint8_t enc_prev_pos;
	uint8_t enc_flags;
  MomentaryButton button;
	public:
    /**
     * Creates a variable of type RotaryEncoder. The pins are the 
     * hardware pins connecting the RotaryEncoder to the microcontroller.
     */
		RotaryEncoder( int pin_button, int pin_a, int pin_b );
   /**
     * This function prepares the RotaryEncoder to operate. This function 
     * should be called within the setup function of an Arduino program. 
     * Otherwise, unpredictable errors may occur while using this library.
     */
		void setup();
   /**
     * This function maintains the RotaryEncoder internal state. This function 
     * must be called within the program's main update loop. 
     * Otherwise, unpredictable errors may occur while using this library.
     */
		void poll();
    /**
     * This function returns the current position of the rotary encoder. 
     */
		int getCurrentPos();
    /**
     * This function sets the maximum available configurations this 
     * RotaryEncoder can track. 
     */
		void setMaxPos( int max );
   /**
     * This function checks if the button is pressed. It returns true if the 
     * button is pressed. Otherwise, this function returns false. 
     */
    uint8_t isPressed();
   /**
     * This function does not cause the button to be read.                  
     * Do not use
     */
    bool wasPressed()
    uint8_t wasPressed();
}
#endif
