#ifndef IMU_H
#define IMU_H

#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <limits.h>
#include <math.h>
#include "Adafruit_Sensor.h"
#include "Adafruit_LSM9DS0.h"
#include <EEPROM.h>

#define CALIB_ADDR 33

#define HEADER 0x2DBD
#define FOOTER 0x7F87

struct CompassDat
{
    uint16_t header;
    float max_x;
    float min_x;
    float max_y;
    float min_y;
    float avg_x;
    float avg_y;
    uint16_t footer;
};


class IMU {
  public: 
    IMU();
    void setup();
    float getAngularSpeed();
    float getDegreesFromNorth();
    void updateSensorFields();
    void dump_mag();
    void calibrate_compass();
    sensors_event_t accel, mag, gyro, temp;
  private:
    const int calibrationLevel = 10;
    int gyroStoppedMin, gyroStoppedMax;
    Adafruit_LSM9DS0 lsm;
    float gyroAvgNoise;  
    CompassDat calib_data;
};
#endif
