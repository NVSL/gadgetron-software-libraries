#ifndef LED_INCLUDED
#define LED_INCLUDED

#include "Arduino.h"

/**
 * This library allows your design to control LEDs (Light Emitting Diodes). 
 * LEDs can be toggled On and Off by supplying them with a controlled amount
 * of power. The LED library supports up to any number of LEDs attached to your
 * design.
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
     * Creates a variable of type LED. The pin parameter is the hardware pin 
     * connecting the LED to the microcontroller.
     */
    LED(int pin): 
        pin(pin), 
        onTime(onTime), 
        offTime(offTime) {
            state = OFF;
            blinking = false;
        }

    /** 
     * This function will update the current state of the LED. If the function
     * blink() was called, then this function will ensure the LED blinks. 
     * This function should be placed at the top of the main 
     * Arduino's update function. The programmer should take care to only make
     * few or short calls to delay() to ensure the LED blinks on time.  
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
     * This function prepares the LED to blink when update() is next called. 
     * The parameters on and off represent the amount of time in milliseconds 
     * for which the LED should remain on and off respectively while blinking.
     */
    void blink(int on, int off) {
        onTime = on;
        offTime = off;
        blink();
    }

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

    /** 
     * This function toggles the LED's state.
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
     * This function turns on the LED
     */
    void turnOn() {
        state = ON;
        digitalWrite(pin, HIGH);
    }

    /**
     * This function turns off the LED
     */
    void turnOff() {
        state = OFF;
        digitalWrite(pin, LOW);
    }

    /**
     * This function prepares the LED to operate. This function should be 
     * called within the main setup function of your main Arduino program. 
     * If not, then very unpredictable things may occur.
     */
    void setup() {
        pinMode(pin, OUTPUT);
        digitalWrite(pin, LOW);
        onTime = offTime = 500;
    }

};
#endif
