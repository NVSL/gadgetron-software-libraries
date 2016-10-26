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

#ifndef LED_INCLUDED
#define LED_INCLUDED

#include "Arduino.h"

/**
 * With these interfaces, you can you turn the LED on and off and make it blink regularly.
 *
 * As usual, be sure to call \p LED.setup() in your \p setup() function.
 */ 
class LED {
    enum {ON, OFF};    //For state stuff

    int pin;   //The pin the LED is connected to
    int onTime;    //The time for the LED to be on during blinking
    int offTime;   //The time for the LED to be off during blinking
    int state;     //The LED's current state (on or off)
    bool blinking; //Whether the LED is 
    unsigned long nextTransition;  //when the next transition time should be when blinking

    public:

    /**
     * rief Constructor
     *
     * The \p pin parameter identifies the physical pin that the LED is
     * connected to.  You won't usually need to call this function, since the
     * code that Gadgetron generates for your design creates an LED object for
     * each LED in your design. 
     *
     * If you use the sketch that came with your robot, you won't need call this.
     */
    LED(int pin): 
        pin(pin), 
        onTime(onTime), 
        offTime(offTime) {
            state = OFF;
            blinking = false;
    }
     /**
      * rief Setup the LED
      *
      * Call this function once in your setup() function.  Without it, the LED
      * won't work properly.
      */
     void setup() {
	  pinMode(pin, OUTPUT);
	  digitalWrite(pin, LOW);
	  onTime = offTime = 500;
     }

    /** 
     * rief Update the state of the LED
     *
     * You should call this function once at the top of your loop() function.
     * It is responsible for making the LED blink if you have used blink().
     */
    void update() {
        if (blinking == true) {
            if (millis() > nextTransition) {
                toggle();
                if (state == OFF)
                {
                    nextTransition = millis() + offTime;
                }
                else if (state == ON)
                {
                    nextTransition = millis() + onTime;
                }
            }
        }
    }

    /** 
     * rief Toggle the LED's state
     *
     * If the LED is on, then this function turns it off. 
     * If the LED is off, then this function turns it on. 
     */
    void toggle() {
        if (state == ON) {
            turnOff();
        } else if (state == OFF) {
            turnOn();
        }
    }

    /**
     * rief Turn the LED on
     */
    void turnOn() {
        state = ON;
        digitalWrite(pin, HIGH);
    }

    /**
     * rief Turn the LED off
     */
    void turnOff() {
        state = OFF;
        digitalWrite(pin, LOW);
    }

    /**
     * rief Set the LED to blink
     *
     * This function makes the LED blink on and off at a specified interval.  It will turn on for \p on milliseconds, turn off for \p off milliseconds, and then repeat.
     *
     * In order for this to work well, you need 
     *
     * 1. Call update() at the top of your loop() function.
     * 
     * 2. Use only very short values for delay().
     */
    void blink(int on, int off) {
        onTime = on;
        offTime = off;
        blink();
    }

#ifndef GTRON_ARDUINO_SKIP
    /**
     * This function prepares the LED to blink when update() is next called. 
     */
    void blink() {
        blinking = true;
        nextTransition = millis() + onTime;
    }

     
    /**
     * Returns whether the LED is in a blinking state or not
     */
    bool isBlinking() {
        return blinking;
    }
#endif
     

};
#endif
