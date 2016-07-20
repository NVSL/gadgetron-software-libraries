#include "IMU.h"
#include <limits.h>

IMU::IMU() { 
  lsm = Adafruit_LSM9DS0(1000);
  gyroStoppedMin = INT_MAX;
  gyroStoppedMax = INT_MIN;
  gyroAvgNoise = 0;

  // Serial.println("IMU Constructor running!");
}

void IMU::setup() {
  EEPROM.get(CALIB_ADDR, calib_data);
  if(calib_data.header == HEADER && calib_data.footer == FOOTER){
    Serial.println("xmax/xmin/ymax/ymin/xavg/yavg");
    Serial.println(calib_data.max_x);
    Serial.println(calib_data.min_x);
    Serial.println(calib_data.max_y);
    Serial.println(calib_data.min_y);
    Serial.println(calib_data.avg_x);
    Serial.println(calib_data.avg_y);
  }else{
    Serial.println("No valid calibration data");
  }

  while (!Serial);  // wait for flora/leonardo
  if(!lsm.begin())
 {
   /* There was a problem detecting the LSM9DS0 ... check your connections */
   Serial.print(F("Ooops, no LSM9DS0 detected ... Check your wiring or I2C ADDR!"));
   while(1);
 }
 Serial.println(F("Found LSM9DS0 9DOF"));
 lsm.setupGyro(lsm.LSM9DS0_GYROSCALE_245DPS); 
 lsm.setupMag(lsm.LSM9DS0_MAGGAIN_2GAUSS);
 lsm.setupAccel(lsm.LSM9DS0_ACCELRANGE_2G);
 for( int i = 0; i < calibrationLevel; i++ ) {
   updateSensorFields();
   int angularSpeed = (int)gyro.gyro.z; 
   gyroAvgNoise += gyro.gyro.z;
   if( angularSpeed > gyroStoppedMax )
     gyroStoppedMax = angularSpeed;
   if( angularSpeed < gyroStoppedMin )
     gyroStoppedMin = angularSpeed;
   delay(100);
 }
 gyroAvgNoise/=calibrationLevel;
 gyroStoppedMax += abs(gyroAvgNoise/8);
 gyroStoppedMin -= abs(gyroAvgNoise/8);
}

float IMU::getAngularSpeed() {
  updateSensorFields();
  float angularSpeed = gyro.gyro.z;
  if( angularSpeed > gyroStoppedMin && angularSpeed < gyroStoppedMax )
    return 0;
  return angularSpeed-gyroAvgNoise;
}
float IMU::getDegreesFromNorth() {
  updateSensorFields();
  // This section of the method computes a Rotation Matrix from accel data
  // Declare references to acceleration vector
  float a1 = accel.acceleration.x;
  float a2 = accel.acceleration.y;
  float a3 = accel.acceleration.z;
  // Declare references to magnetic field vector
  float m1 = mag.magnetic.x;
  float m2 = mag.magnetic.y;
  float m3 = mag.magnetic.z;

  if(calib_data.header == HEADER && calib_data.footer == FOOTER){
    m1 -= calib_data.avg_x;
    m2 -= calib_data.avg_y;
  }

  /**
  // Determine magnitude
  float mag = sqrt((a1*a1)+(a2*a2)+(a3*a3));
  // Normalize acceleration vector
  float x1 = a1/mag;
  float x2 = a2/mag;
  float x3 = a3/mag;
  // Define constant used frequently in computing Rotation Matrix
  float lamda = ((1-x3)/((x2*x2)+(x1*x1)));
  // Compute Rotation Matrix
  float rot[2][3] = {
    { 1 - (lamda * x1 * x1 ), -1 * lamda * x1 * x2, x1 },
    { -1 * x1 * x2, 1 - (lamda * x2 * x2 ), x2 }
    //{ -1 * x1, -1 * x2, x3 }
  };
  // Find rotated magnometer vector 
  float b1 = ((rot[0][0]*m1)+(rot[0][1]*m2)+(rot[0][2]*m3)); 
  float b2 = ((rot[1][0]*m1)+(rot[1][1]*m2)+(rot[1][2]*m3)); 
  */
  // Finally, calculate the angle
  float theta = -atan2( m2, m1) * 180 / PI;
  // if( theta < 0 )
    // theta += 360;
  return theta;
}

void IMU::updateSensorFields() {
  lsm.getEvent(&accel, &mag, &gyro, &temp);
}

void IMU::dump_mag(){
  updateSensorFields();
  Serial.print(mag.magnetic.x,4);
  Serial.print(",");
  Serial.print(mag.magnetic.y,4);
  Serial.print(",");
  Serial.println(mag.magnetic.z,4);
}

void IMU::calibrate_compass(){
  int i;
  calib_data.header = HEADER;
  calib_data.max_x = -999;
  calib_data.min_x = 999;
  calib_data.max_y = -999;
  calib_data.min_y = 999;
  calib_data.avg_x = 0;
  calib_data.avg_y = 0;
  calib_data.footer = FOOTER;

  int limit = 5000;
  
  for(i=0;i<limit;i++){
    Serial.println(i);
    updateSensorFields();
    if(mag.magnetic.x > calib_data.max_x)
      calib_data.max_x = mag.magnetic.x;
    if(mag.magnetic.y > calib_data.max_y)
      calib_data.max_y = mag.magnetic.y;

    if(mag.magnetic.x < calib_data.min_x)
      calib_data.min_x = mag.magnetic.x;
    if(mag.magnetic.y < calib_data.min_y)
      calib_data.min_y = mag.magnetic.y;

    calib_data.avg_x += mag.magnetic.x;
    calib_data.avg_y += mag.magnetic.y;
  }

  calib_data.avg_x /= limit;
  calib_data.avg_y /= limit;

  EEPROM.put(CALIB_ADDR, calib_data);

}





