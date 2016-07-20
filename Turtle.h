/**
 * Filename: Turtle.h \n
 * Author: Michael Gonzalez and Paula Quach \n
 * Description: This class is designed to emulate Turtle Graphics, a popular
 *              tool to teach basic Computer Science concepts, with robots
 *              using an Arduino processor. These robot turtles have similiar
 *              commands to their virtual counter parts; they can move and turn
 *              through their physical environment. \n
 * Requirements: In order to use this class, the driving robot must have a 
 *               dual motor driver and a Adafruit LSM9DS0. Optionally, the
 *               turtle can also have a servo-pen.
 */
#ifndef ROBOTTURTLE_H
#define ROBOTTURTLE_H

#include <Motor.h>
#include <Servo.h>
#include <IMU.h>
#include <Arduino.h>
#include <math.h>
#include <Servo.h>


class RobotTurtle
{
  public:
    /** This is the simplest constructor for a robot turtle. It only takes a
      * motor as an argument */
    RobotTurtle(Motor * motor);
    /** This constructor takes a motor, a servo, and the servo's pin as 
      * arguments. Use this constructor if you want to emulate the Turtle's
      * pen features. */
    RobotTurtle(Motor * motor, Servo * servo, byte servoPin ); 
    /** Move the turtle forward for one second. The turtle will move at the
      * speed defined by setSpeed. The default speed is full speed */
    void forward();
    /** Move the turtle backwards for one second. The turtle will move at the
      * speed defined by setSpeed. The default speed is full speed */
    void backward();
    /** Move the turtle forward for ms milliseconds. The turtle will move at the
      * speed defined by setSpeed. The default speed is full speed */
    void forward(int ms);
    /** Move the turtle backwards for ms milliseconds. The turtle will move at 
      * the speed defined by setSpeed. The default speed is full speed */
    void backward(int ms);
    /** Spin the turtle to turn to the specified degree. The angle is relative
      * to the turtle's current orientation */
    void turn(float degree);

    /* Point at an absolute compass direction */
    void turn_to(float degree);

    /** Turn the turtle to its relative right */
    void turnRight();
    /** Turn the turtle to its relative left */
    void turnLeft();
    /** Raises the turtle's pen off the ground. */
    void penUp();
    /** Drops the turtle's pen to the ground. */
    void penDown();
    /** Sets the turtle up to function correctly. */
    void setup();

    /** Defines the maximum speed the motor will drive */
    void setSpeed( int speed );

    /* Maximum speed allowed when turning (0-255) */
    void setTurnSpeed(int speed);

    /** Defines the minimum speed the motor will drive. This is useful for 
      * configuring turning */
    void setMinSpeed( int minSpeed);

    /** Defines the proportional integral derivative constants */
    void setPID( float p, float i, float d );

    /* Turn off the motors and just print values */
    void debug_mode();

    /* Record samples from the IMU to see how messed up it is */
    void imu_log();

    /* Calibrate the compass */
    void calibrate();

  private:
    Motor * _motor;
    Servo * _servo;
    byte _servoPin;
    IMU _imu;
    float startingAngle;
    int _maxSpeed = 255;
    int _maxSpeedTurn = 100;
    int _minSpeed = 21;
    // PID Fields
    // float error;
    // float desiredAngle = 0;
    // float actualAngle = 0;
    float kP = 1.3;
    float kI = .25;
    float kD = .7;
    float accuracy = 5.0;
    bool isSpinningRight;
    // PID Functions
    float getError(float desired);
    void turnToAngle(float angle);
    // float determineDesiredAngle(float angle);
    void brake();
    float getDeltaTime();
    void spinPID(float error);
    void spinDumb(float error);
    // Math Fields
    // float velocity = 0;
    float integral = 0;
    float currentTime = 0;
    float prevTime = 0;

    float delta_t_sum;
    int delta_t_samples;
    bool _debug = false;

};

#endif
