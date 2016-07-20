/**
 * Filename: Turtle.cpp
 * Author: Michael Gonzalez and PQ
 * Description: This class is designed to emulate Turtle Graphics, a popular
 *              tool to teach basic Computer Science concepts, with robots
 *              using an Arduino processor. These robot turtles have similiar
 *              commands to their virtual counter parts; they can move and turn
 *              through their physical environment.
 * Requirements: In order to use this class, the driving robot must have a 
 *               dual motor driver and a Adafruit LSM9DS0. Optionally, the
 *               turtle can also have a servo-pen.
 */

#include "Turtle.h"

int sgn(float a){
  return ((a>0) - (a<0));
}

// Constructor
RobotTurtle::RobotTurtle(Motor * motor, Servo * servo, byte servoPin ) {
  _motor = motor;
  _servo = servo;
  _servoPin = servoPin;
}

RobotTurtle::RobotTurtle(Motor * motor) {
  _motor = motor;
  _servo = NULL;
}

// RobotTurtle::RobotTurtle(Motor * motor, Servo * servo){}

// Public Functions
void RobotTurtle::setup() {
  _motor->setup();
  _imu.setup();
  startingAngle = _imu.getDegreesFromNorth();
  // If this Turtle has a servo, then set it up
  if( _servo != NULL ) {
    _servo->attach(_servoPin);
  }
}

void RobotTurtle::setSpeed( int speed ) {
  if( speed < _minSpeed)
    _maxSpeed = _minSpeed;
  else if( speed > 255 )
    _maxSpeed = 255;
  else
    _maxSpeed = speed;
}

void RobotTurtle::setTurnSpeed(int speed){
  if(speed < _minSpeed || speed > 255)
    return;
  _maxSpeedTurn = speed;
}

void RobotTurtle::setMinSpeed( int minSpeed ) {
  _minSpeed = minSpeed;
}

void RobotTurtle::forward() { forward(1000); }

void RobotTurtle::backward() { backward(1000); }

void RobotTurtle::forward(int ms) {
  //desiredAngle = _imu.getDegreesFromNorth();
  _motor->forward(_maxSpeed);
  delay(ms);
  brake();
  //turnToAngle();
}

void RobotTurtle::backward(int ms) {
  //desiredAngle = _imu.getDegreesFromNorth();
  _motor->backward(_maxSpeed);
  delay(ms);
  brake();
  //turnToAngle();
}

void RobotTurtle::turn( float degree ) {
  turnToAngle(_imu.getDegreesFromNorth() + degree);
}

void RobotTurtle::turn_to(float degree){
  turnToAngle(degree);
}

void RobotTurtle::turnLeft() {
  turn( -90 );
}

void RobotTurtle::turnRight() {
  turn( 90 );
}

void RobotTurtle::penUp() {
  if( _servo != NULL )
    _servo->write(50);
}
void RobotTurtle::penDown() {
  if( _servo != NULL )
    _servo->write(0);
}
void RobotTurtle::setPID( float p, float i, float d ) {
  kP = p;
  kI = i;
  kD = d;
}

// Private Functions

void RobotTurtle::turnToAngle(float desired_angle) {
  integral = 0;
  float error = getError(desired_angle);
  getDeltaTime();

  while(abs(error) > accuracy){
    while( abs( error ) > accuracy || abs(_imu.getAngularSpeed()) > 1.0 ) {
      spinPID(error);
      // spinDumb(error);
      error = getError(desired_angle);
    }
    delay(500);
    _motor->brake();
  }

  _motor->stop();
  integral = 0;
}

void RobotTurtle::spinDumb(float error){
  if(error > 0){
    _motor->spinLeft(50);
  }else if(error < 0){
    _motor->spinRight(50);
  }
}

void RobotTurtle::spinPID(float error) {
  // Setup overhead
  float deltaTime = getDeltaTime();

  //float derivative = ((error - prevError)/deltaTime);
  float derivative = _imu.getAngularSpeed();
  integral += error * deltaTime;

  // Calculate the velocity magnitude
  float p,i,d;
  p = kP * error;

  if(integral > 40)
    integral = 40;
  if(p > _minSpeed*1.4)
    integral = 0;

  i = kI * integral;
  d = -kD * derivative;

  float velocity = p + i + d;

  
  //Constrain velocity to min/max limits
  if(abs(velocity) > _maxSpeedTurn){
    velocity = _maxSpeedTurn * sgn(velocity);
  }


  if(_debug){
    delta_t_sum += deltaTime;
    delta_t_samples++;
    if(delta_t_samples == 100){
      Serial.print("Latency: ");
      Serial.print((delta_t_sum / delta_t_samples)*1000, 2);
      Serial.println("ms");

      Serial.print("Heading: ");
      Serial.println(_imu.getDegreesFromNorth());

      Serial.print("Error: ");
      Serial.println(error);

      Serial.print("P: ");
      Serial.println(p);
      Serial.print("I: ");
      Serial.println(i);
      Serial.print("D: ");
      Serial.println(d);

      Serial.print("Sum: ");
      Serial.println(velocity);
      Serial.println("");

      delta_t_sum = 0;
      delta_t_samples = 0;
    }
  }

  //positive error = turn left
  //negative error = turn right

  // Spin!
  if( velocity > 0 ) {
    // if( isSpinningRight ) { // Check spin direction
    //   brake(); // Prevents shorts
    // }
    _motor->spinLeft(velocity);
    isSpinningRight = false;
  }
  else {
    // if( !isSpinningRight ) { // Check spin direction
    //   brake(); // Prevents shorts
    // }
    _motor->spinRight(-velocity);
    isSpinningRight = true;
  }
}

// void RobotTurtle::determineDesiredAngle(float angle) {
//   float currentAngle = _imu.getDegreesFromNorth();
//   desiredAngle = fmod( currentAngle + angle, 360 );
// }

void RobotTurtle::brake() {
  _motor->brake();
  delay(350);
}

float RobotTurtle::getDeltaTime() {
  prevTime = currentTime;
  currentTime = (float)millis()/1000;
  return (currentTime - prevTime);
}

float RobotTurtle::getError(float desiredAngle) {
  float angle = _imu.getDegreesFromNorth();
  float error = fmod((fmod( desiredAngle - angle, 360)+360), 360);
  if( error > 180 )
    error -= 360;
  return error;
}

void RobotTurtle::debug_mode(){
  _motor->disable();
  _debug = true;
}

void RobotTurtle::imu_log(){
  if(!_debug)
    return;
  while(1){
    _imu.dump_mag();
    delay(100);
  }
}


void RobotTurtle::calibrate(){
  _motor->spinLeft(35);
  _imu.calibrate_compass();
  _motor->brake();
}






