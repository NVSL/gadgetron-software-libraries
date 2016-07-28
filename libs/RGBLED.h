#ifndef RGBLED_H
#define RGBLED_H

#include <Arduino.h>

class RGBLED
{
  public:
     RGBLED(int red, int green, int blue, bool common_anode=true);
     void set(int red, int green, int blue);
     void fade(int red, int green, int blue, int step, int period);
     void setup();
     void loop();
     
 private: 
     // pins for the colors
     const int red_pin, green_pin, blue_pin;
     
     // variable used to save current color
     int prev_red, prev_green, prev_blue;
     
     // cathode default is dark, anode is bright 
     const bool common_anode;

};

#endif

