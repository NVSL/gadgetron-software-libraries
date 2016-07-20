#include "Motor.h"

#define MAX_SPEED 255

Motor::Motor( uint8_t STBY, uint8_t PWMA, uint8_t AIN1, uint8_t AIN2,
              uint8_t PWMB, uint8_t BIN1, uint8_t BIN2) {
  this->STBY = STBY;
  this->PWMA = PWMA;
  this->AIN1 = AIN1;
  this->AIN2 = AIN2;
  this->PWMB = PWMB;
  this->BIN1 = BIN1;
  this->BIN2 = BIN2;
  polarity = 0;
}

void Motor::setup() {
  if(IS_BLOCKED) return;
  claimPins();
  state = HAS_SETUP;
}

void Motor::claimPins() {
  pinMode(this->STBY, OUTPUT);
  pinMode(this->PWMA, OUTPUT);
  pinMode(this->AIN1, OUTPUT);
  pinMode(this->AIN2, OUTPUT);
  pinMode(this->PWMB, OUTPUT);
  pinMode(this->BIN1, OUTPUT);
  pinMode(this->BIN2, OUTPUT);
}

void Motor::changePolarity()
{
  polarity = polarity == 0 ? 1 : 0;
}

void Motor::_moveBoth( uint8_t speed, uint8_t polarity ) {
  move( MOTOR_A, speed, polarity);
  move( MOTOR_B, speed, polarity);
}
void Motor::move(uint8_t motor, uint8_t speed=255, uint8_t direction=0) {
  if(IS_BLOCKED) return;
  int pins[MOTOR_PIN_C] = MOTOR_PIN_ARRAY;
  #ifdef GADGET_MANAGER
  GadgetManager::freePins( pins, MOTOR_PIN_C ); 
  #endif
  state |= 8;
  digitalWrite(STBY, HIGH);
  bool inPin1 = direction == 1 ? HIGH : LOW;
  bool inPin2 = direction == 1 ? LOW  : HIGH;
  if( motor == MOTOR_A ) {
    digitalWrite(AIN1, inPin1);
    digitalWrite(AIN2, inPin2);
    analogWrite(PWMA, speed);
  }
  else {
    digitalWrite(BIN1, inPin1);
    digitalWrite(BIN2, inPin2);
    analogWrite(PWMB, speed);
  }
}

void Motor::brake() {
  if(IS_BLOCKED) return;
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, LOW);
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, LOW);
  stop();
}


unsigned char Motor::swapDirections() {
  unsigned char oldState = (~DIRECTION_BIT) & state;
  state = oldState | ((state&DIRECTION_BIT) ^ DIRECTION_BIT);
  return state;
}

void Motor::stop() {
  if(IS_BLOCKED) return;
  digitalWrite(STBY,LOW);
  state &= (~MOVING_BIT);
  int pins[MOTOR_PIN_C] = MOTOR_PIN_ARRAY;
  #ifdef GADGET_MANAGER
  GadgetManager::reenablePins( pins, MOTOR_PIN_C ); 
  #endif
}

void Motor::forward()
{
  forward(MAX_SPEED);
}


void Motor::forward(uint8_t speed) {
  _moveBoth(speed, polarity);
}

void Motor::backward()
{
  backward(MAX_SPEED);
}

void Motor::backward(uint8_t speed) {
  _moveBoth(speed, polarity == 1 ? 0 : 1);
}

void Motor::accelerateForward( uint8_t startSpeed, uint8_t endSpeed, int rate ) {
    this->accelerate( startSpeed, endSpeed, rate, &Motor::forward );
}
void Motor::accelerateBackward( uint8_t startSpeed, uint8_t endSpeed, int rate ) {
    this->accelerate( startSpeed, endSpeed, rate, &Motor::backward);
}

void Motor::accelerate( uint8_t startSpeed, uint8_t endSpeed, int rate, void (Motor::*movF)(uint8_t) ) {
  int dir = startSpeed < endSpeed ? 1 : -1;
  for(uint8_t i = startSpeed; i != endSpeed; i+=dir ) {
      (this->*movF)(i);
      delay(rate);
  }
}

void Motor::spinRight()
{
   spinRight(MAX_SPEED);
}

void Motor::spinRight(uint8_t speed) {
    move( MOTOR_A_ORIG, speed, 0);
    move( MOTOR_B_ORIG, speed, 1);
}

void Motor::spinLeft()
{
     spinLeft(MAX_SPEED);
}

void Motor::spinLeft(uint8_t speed) {
    move( MOTOR_A_ORIG, speed,  1);
    move( MOTOR_B_ORIG, speed,  0);
}

void Motor::forwardAndRight() {
  forwardAndRight(MAX_SPEED, .5);
}

void Motor::forwardAndRight( uint8_t speed, float ratio ) {
  move( MOTOR_A, speed, polarity);
  move( MOTOR_B, (uint8_t)(speed*ratio), polarity);
}

void Motor::forwardAndLeft() {
  forwardAndLeft(MAX_SPEED, .5);
}

void Motor::forwardAndLeft( uint8_t speed, float ratio ) {
  move( MOTOR_A, (uint8_t)(speed*ratio), polarity);
  move( MOTOR_B, speed, polarity);
}

bool Motor::isMoving() { return (state & MOVING_BIT); }

void Motor::disable(){
  state |= BLOCKED;
}


