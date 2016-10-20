/*************************************************** 
  This is a library for our I2C LED Backpacks

  Designed specifically to work with the Adafruit LED Matrix backpacks 
  ----> http://www.adafruit.com/products/
  ----> http://www.adafruit.com/products/

  These displays use I2C to communicate, 2 pins are required to 
  interface. There are multiple selectable I2C addresses. For backpacks
  with 2 Address Select pins: 0x70, 0x71, 0x72 or 0x73. For backpacks
  with 3 Address Select pins: 0x70 thru 0x77

  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  MIT license, all text above must be included in any redistribution
 ****************************************************/
#ifndef Adafruit_LEDBackpack_h
#define Adafruit_LEDBackpack_h

#if (ARDUINO >= 100)
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif


 #include <Wire.h>

#include "Adafruit_GFX.h"

#define LED_ON 1
#define LED_OFF 0

#define LED_RED 1
#define LED_YELLOW 2
#define LED_GREEN 3
 


#define HT16K33_BLINK_CMD 0x80
#define HT16K33_BLINK_DISPLAYON 0x01
#define HT16K33_BLINK_OFF 0
#define HT16K33_BLINK_2HZ  1
#define HT16K33_BLINK_1HZ  2
#define HT16K33_BLINK_HALFHZ  3

#define HT16K33_CMD_BRIGHTNESS 0xE0

#define SEVENSEG_DIGITS 5

// this is the raw HT16K33 controller
class Adafruit_LEDBackpack {
 public:

  Adafruit_LEDBackpack(void);
  
#ifndef GTRON_ARDUINO_SKIP
  void begin(uint8_t _addr);
#endif
  /**
   * \brief Set brightness
   *
   * Set the brightness of the display: 0 (very dim) to 255 (bright!).
   */
  void setBrightness(uint8_t b);

    
#ifndef GTRON_ARDUINO_SKIP
  void blinkRate(uint8_t b);
#endif
  
  /**
   * \brief Update display.
   *
   * Update the display to show its current contents.  None of the changes you make will take effect until you call this function.
   */
  void writeDisplay(void);

  /**
   * \brief Clear the display.
   */
  void clear(void);

  uint16_t displaybuffer[8]; 

  
#ifndef GTRON_ARDUINO_SKIP
  void init(uint8_t a);
#endif
 protected:
  uint8_t i2c_addr;
};

class Adafruit_AlphaNum4 : public Adafruit_LEDBackpack {
 public:
  Adafruit_AlphaNum4(void);

  void writeDigitRaw(uint8_t n, uint16_t bitmask);
  void writeDigitAscii(uint8_t n, uint8_t ascii, boolean dot = false);

 private:


};

class Adafruit_24bargraph : public Adafruit_LEDBackpack {
 public:
  Adafruit_24bargraph(void);

  void setBar(uint8_t bar, uint8_t color);

 private:
};


class Adafruit_8x16matrix : public Adafruit_LEDBackpack, public Adafruit_GFX {
 public:
  Adafruit_8x16matrix(void);

  void drawPixel(int16_t x, int16_t y, uint16_t color);

 private:
};

class Adafruit_8x16minimatrix : public Adafruit_LEDBackpack, public Adafruit_GFX {
 public:
  Adafruit_8x16minimatrix(void);

  void drawPixel(int16_t x, int16_t y, uint16_t color);

 private:
};

class Adafruit_8x8matrix : public Adafruit_LEDBackpack, public Adafruit_GFX {
public:
     /**
      * \brief Constructor
      *
      * If you use the sketch that came with your robot, you won't need call this.
      */
  Adafruit_8x8matrix(void);

     /**
      * \brief Draw a pixel
      *
      * Turn on the pixel at location \p x, \p y.  If \p color == 0, turn it off. Otherwise turn it on.
      */
     void drawPixel(int16_t x, int16_t y, uint16_t color);
     
     /**
      * \brief Setup the display.
     *
     * Call this method in your \p setup() function.
     */
  void setup();

 private:
};

class Adafruit_BicolorMatrix : public Adafruit_LEDBackpack, public Adafruit_GFX {
 public:
  Adafruit_BicolorMatrix(void);

  void drawPixel(int16_t x, int16_t y, uint16_t color);

 private:
};


#define DEC 10
#define HEX 16
#define OCT 8
#define BIN 2
#define BYTE 0

/**
 * The methods for the display allow you to display numeric values, control the
 * colon (':'), and change the display's brightness.
 *
 * After you call method to display a value or update the colon, you need to
 * explicitly update the display by calling \p writeDisplay(), otherwise, you
 * won't see the effect of your changes.
 */
class Adafruit_7segment : public Adafruit_LEDBackpack {
 public:

  /**
   * \brief Constructor
   *
   * If you use the sketch that came with your robot, you won't need call this.
   */
  Adafruit_7segment();

#ifndef GTRON_ARDUINO_SKIP
  size_t write(uint8_t c);
#endif
  
  /**
   * \brief Setup the display
   *
   * Call this function once in your setup() function.  Without it, the display
   * won't work properly.
   */
  void setup();
  
#ifndef GTRON_ARDUINO_SKIP
  void print(char d,int type = BYTE);
  void print(unsigned char d,int type = BYTE);
  void print(int d,int type = DEC);
  void print(unsigned int d,int type = DEC);
  void print(long d,int type = DEC);
  void print(unsigned long d,int type = DEC);
  void print(double d,int precision = 2);

  void println(char d,int type = BYTE);
  void println(unsigned char d,int type = BYTE);
  void println(int d,int type = DEC);
  void println(unsigned int d,int type = DEC);
  void println(long d,int type = DEC);
  void println(unsigned long d,int type = DEC);
  void println(double d,int precision = 2);
  void println(void);

  
  void writeDigitRaw(uint8_t x, uint8_t bitmask);
  void writeDigitNum(uint8_t x, uint8_t num, boolean dot = false);
#endif
  
  /**
   * \brief Draw the colon on the display
   *
   * If \p state is \p true, light up the colon.  If \p state is \p false, turn it off.  
   *
   * Call \p writeDisplay() to see the effect.
   */
  void drawColon(boolean state);

  /**
   * \brief Write an integer to the display
   *
   * By default use base 10.  Alternately, provide \p DEC, \p HEX, \p OCT, or \p BIN to print in decimal, hexidecimal, octal, or binary.
   */
  void printNumber(long, uint8_t base= DEC);
  /**
   * \brief Write an float to the display
   *
   * By default use base 10.  Alternately, provide \p DEC, \p HEX, \p OCT, or \p BIN to print in decimal, hexidecimal, octal, or binary.
   * By fefault, print two digits of the fraction.  Pass \p digits to show more or less.
   */
  void printFloat(double, uint8_t digits= 2, uint8_t base= DEC);
  /**
   * \brief Print an error pattern
   */
  void printError(void);

#ifndef GTRON_ARDUINO_SKIP
  void writeColon(void);
#endif
  
 private:
  uint8_t position;
};
#endif // Adafruit_LEDBackpack_h

