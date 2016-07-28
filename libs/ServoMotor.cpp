#include "ServoMotor.h"
#include <Servo.h>


ServoMotor::ServoMotor( int pin ) {
  this->pin = pin;
  this->state = 0;
  this->next = 0;
}

void ServoMotor::setup() {
  this->state |= HAS_SETUP;
  this->attach();
  GadgetManager::registerServo( this );
}

void ServoMotor::attach() {
  this->state |= ATTACHED;
  if( IS_BLOCKED ) return;
  this->servo.attach( pin );
}

void ServoMotor::detach() {
  this->state &= (~ATTACHED);
  this->_detach();
}
void ServoMotor::_detach() {
  this->servo.detach();
  TCCR1B=0;
  TCCR1B=_BV(CS11);
  TCCR1B=_BV(CS10);
  TCCR1A=_BV(WGM10);
  TIMSK1=0;
}

void ServoMotor::rotate( int degrees ) {
  if( !IS_BLOCKED && ( state&ATTACHED ) && !servo.attached() )
    this->servo.attach( pin );
  this->servo.write( degrees );
}

void ServoMotor::block() {
  this->state |= BLOCKED;
  this->_detach();
}

void ServoMotor::enable() {
  this->state &= (~BLOCKED);
}
