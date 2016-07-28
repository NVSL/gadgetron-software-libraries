#include "Pincer.h"

Pincer::Pincer(uint8_t pin)
{
    this->pin = pin;
    state = PINCER_OPEN;
}

void Pincer::setup()
{
    srv = new ServoMotor(pin);
    srv ->setup();
}

void Pincer::changeState()
{
    if(state)
        state = PINCER_CLOSED;
    else
        state = PINCER_OPEN;
}

void Pincer::toggle()
{
    if(state)
        close();
    else
        open();
}

void Pincer::open()
{
    open(MIN_ANGLE);
}

void Pincer::open(int angle)
{
    state = PINCER_OPEN;
    if(angle >= MIN_ANGLE && angle <= MAX_ANGLE)
        srv->rotate(angle);
}

void Pincer::close()
{
    state = PINCER_CLOSED;
    srv->rotate(MAX_ANGLE);
}

void Pincer::onAndOff(int time, int times)
{
    for(int i = 0; i < times; i++)
    {
        toggle();
        delay(time);
    }
}

void Pincer::setOpen(int angle)
{
    MIN_ANGLE = angle;
}

void Pincer::setClose(int angle)
{
    MAX_ANGLE = angle;
}

bool Pincer::isOpen()
{
    return state == PINCER_OPEN;
}

void Pincer::setMin(int min)
{
    min_angle = min;
}

void Pincer::setMax(int max)
{
    max_angle = max;
}
