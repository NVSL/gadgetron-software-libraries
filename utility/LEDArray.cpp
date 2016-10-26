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

#include "LEDArray.h"

LEDArray::LEDArray():
     Adafruit_8x8matrix()
{
    rotation = DOWN;
    setRotation(DOWN);
}
LEDArray::LEDArray(int dummyPin, int dummyPin2)
{
    rotation = DOWN;
    setRotation(DOWN);
}

void LEDArray::setup()
{
     begin(0x70);
     clear();
     writeDisplay();
}

void LEDArray::drawHappyFace()
{
     clear();
     drawBitmap(0, 0, smile_bmp, 8, 8, LED_ON);
     writeDisplay();
}

void LEDArray::drawNeutralFace()
{
     clear();
     drawBitmap(0, 0, neutral_bmp, 8, 8, LED_ON);
     writeDisplay();
}

void LEDArray::drawSadFace()
{
     clear();
     drawBitmap(0, 0, frown_bmp, 8, 8, LED_ON);
     writeDisplay();
}

void LEDArray::turnClockwise()
{
    if(rotation == DOWN)
        rotation = LEFT;
    else
        rotation += 1;

    setRotation(rotation);
}

void LEDArray::turnCounterClockwise()
{
    if(rotation == LEFT)
        rotation = DOWN;
    else
        rotation -= 1;

    setRotation(rotation);
}

void LEDArray::printText(String text)
{
     clear();
     setTextSize(1);
    //false means nice scroll, true means each char appears and then scrolls off
     setTextWrap(false);
     setTextColor(LED_ON);

    //negative number of characters * 8
    for (int8_t x=0; x>=-96; x--)
    {
	 clear();
	 setCursor(x,0);
	 print(text);
	 writeDisplay();
	 delay(100);
    }
}

void LEDArray::drawPix(int x, int y)
{
     drawPixel(x, y, LED_ON);
     writeDisplay();
}

void LEDArray::drawLine(int x1, int y1, int x2, int y2)
{
     Adafruit_8x8matrix::drawLine(x1, y1, x2, y2, LED_ON);
     writeDisplay();
}

void LEDArray::drawRec(int x1, int y1, int x2, int y2)
{
     Adafruit_8x8matrix::drawRect(x1, y1, x2, y2, LED_ON);
     writeDisplay();
}

void LEDArray::fillRec(int x1, int y1, int x2, int y2)
{
     Adafruit_8x8matrix::fillRect(x1, y1, x2, y2, LED_ON);
     writeDisplay();
}

void LEDArray::drawCircle(int x, int y, int r)
{
     Adafruit_8x8matrix::drawCircle(x, y, r, LED_ON);
     writeDisplay();
}

void LEDArray::fillCircle(int x, int y, int r)
{
     Adafruit_8x8matrix::fillCircle(x, y, r, LED_ON);
     writeDisplay();
}

void LEDArray::clear()
{
     clear();
     writeDisplay();
}

void LEDArray::blink(int rate)
{
     blinkRate(rate);
}
