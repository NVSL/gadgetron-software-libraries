#ifndef PINCER_INCLUDED
#define PINCER_INCLUDED

#include <Arduino.h>
#include "ServoMotor.h"
#define PINCER_OPEN 1
#define PINCER_CLOSED  0
/**
 * Filename: Pincer.h
 * Description: Grab things, pinch things, destroy the world.
 */

class Pincer
{
    //states
    uint8_t pin;
    uint8_t state;
    ServoMotor * srv;

    public:
        /**
         * Constructor assigning the pin to variable and default is an open state
         */
        Pincer(uint8_t pin);
        void setup();
        void toggle();
        void open();
        void open(int angle);
        void close();
        void onAndOff(int time, int times);
        void changeState();
        void setOpen(int angle);
        void setClose(int angle);
        bool isOpen();
        void setMin(int min);
        void setMax(int max);

    private:
        int MAX_ANGLE = 84;
        int MIN_ANGLE = 40;
        int max_angle = 84;
        int min_angle = 40;
};

#endif
