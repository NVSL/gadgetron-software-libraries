#ifndef BREAKOUTPINS_H
#define BREAKOUTPINS_H

#include "Arduino.h"

class OneDigitalPin {
  private:
  
    uint8_t pin;
    // read_write Checks if pinMode needs to be changed as
    // Either as input (1) or output (0), it also
    // helps preventing pinMode init always. 
    int read_write;
    
  public:

    // Costructor 
    // Declares one pin
    OneDigitalPin(uint8_t pin): pin(pin), read_write(-1) {};

    // Write to pin 
    // Parameter "value" expects HIGH (1) or LOW (0) as input
    void write (uint8_t value) {
      if (read_write != 0 ) {
        pinMode(pin, OUTPUT);
        read_write = 0;
      }
      digitalWrite(pin, value);
    }

    // Read pin value
    // returns: HIGH (1) or LOW (0)
    int read () {
      if (read_write != 1 ) {
        pinMode(pin, INPUT);
        read_write = 1;
      }
      return digitalRead(pin);
    }

    // Initialize pin
    void setup () {
      // Does nothing
    }
  
};

class FourDigitalPin {
  private:
  
    uint8_t pin1;
    uint8_t pin2;
    uint8_t pin3;
    uint8_t pin4;
    // read_write Checks if pinMode needs to be changed as
    // Either as input (1) or output (0), it also
    // helps preventing pinMode init always. 
    int read_write[4];
    
  public:

    // Costructor 
    // Declares four pins
    FourDigitalPin
        (uint8_t pin1, uint8_t pin2, uint8_t pin3, uint8_t pin4):
        pin1(pin1), pin2(pin2), pin3(pin3), pin4(pin4) 
        {
          memset(read_write, -1, sizeof(read_write));
        };

    // Write to pin1
    // Parameter "value" expects HIGH (1) or LOW (0) as input
    void writeOne (uint8_t value) {
      if (read_write[0] != 0 ) {
        pinMode(pin1, OUTPUT);
        read_write[0] = 0;
      }
      digitalWrite(pin1, value);
    }

    // Read pin1 value
    // returns: HIGH (1) or LOW (0)
    int readOne () {
      if (read_write[0] != 1 ) {
        pinMode(pin1, INPUT);
        read_write[0] = 1;
      }
      return digitalRead(pin1);
    }

    // Write to four pins 
    // Parameter "value" expects HIGH (1) or LOW (0) as input
    void writeTwo (uint8_t value) {
      if (read_write[1] != 0 ) {
        pinMode(pin2, OUTPUT);
        read_write[1] = 0;
      }
      digitalWrite(pin2, value);
    }

    // Read pin value
    // returns: HIGH (1) or LOW (0)
    int readTwo () {
      if (read_write[1] != 1 ) {
        pinMode(pin2, INPUT);
        read_write[1] = 1;
      }
      return digitalRead(pin2);
    }

    // Write to four pins 
    // Parameter "value" expects HIGH (1) or LOW (0) as input
    void writeThree (uint8_t value) {
      if (read_write[2] != 0 ) {
        pinMode(pin3, OUTPUT);
        read_write[2] = 0;
      }
      digitalWrite(pin3, value);
    }

    // Read pin value
    // returns: HIGH (1) or LOW (0)
    int readThree () {
      if (read_write[2] != 1 ) {
        pinMode(pin3, INPUT);
        read_write[2] = 1;
      }
      return digitalRead(pin3);
    }

    // Write to four pins 
    // Parameter "value" expects HIGH (1) or LOW (0) as input
    void writeFour (uint8_t value) {
      if (read_write[3] != 0 ) {
        pinMode(pin4, OUTPUT);
        read_write[3] = 0;
      }
      digitalWrite(pin4, value);
    }

    // Read pin value
    // returns: HIGH (1) or LOW (0)
    int readFour () {
      if (read_write[3] != 1 ) {
        pinMode(pin4, INPUT);
        read_write[3] = 1;
      }
      return digitalRead(pin4);
    }
    

    // Initialize pin
    void setup () {
      // Does nothing
    }
    
};


class OneAdcPin {
  private:
    uint8_t pin;
    
  public:
    // Costructor 
    // Declares one analog pin
    OneAdcPin(uint8_t pin): pin(pin) {};

    // Reads analog pin value
    // returns: analog value in a range from 0 to 1024
    int read () {
      return analogRead(pin);
    }

    // Initialize pin
    void setup () {
      pinMode(pin, INPUT);
    }
  
};

class OnePwmPin {
  private:
    uint8_t pin;
    
  public:
    // Costructor 
    // Declares one analog pin
    OnePwmPin(uint8_t pin): pin(pin) {};

    // Writes PWM duty cycle to analog pin 
    // Parameter "value" expects pwm duty cycle as input
    void write (uint8_t dutyCycle) {
      analogWrite(pin, dutyCycle);
    }

    // Initialize pin
    void setup () {
      pinMode(pin, OUTPUT);
    }
  
};

#endif



