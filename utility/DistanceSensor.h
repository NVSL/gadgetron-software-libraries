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

#ifndef DISTANCE_SENSOR_H
#define DISTANCE_SENSOR_H


#include <Arduino.h>
/**
 * This library lets you read the distance from the distance sensor.
 */
class DistanceSensor{
public:
     /**
      * rief Constructor
      *
      * Set the \p analog_pin that connects to the sensor.
      *
      * If you use the sketch that came with your robot, you won't need call this.
      */
    DistanceSensor(int analog_pin);

    /**
     * rief Setup the sensor.
     *
     * Call this method in your \p setup() function.
     */
    void setup();

    /**
     * rief How far?
     *
     * Get the distance reading from the sensor in cm.
     */
    int get_distance();
private:
    int _pin;

};




#endif
