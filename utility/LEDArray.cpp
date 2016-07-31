/* Copyright (c) <2016> <mmg005@eng.ucsd.edu >
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

LEDArray::LEDArray()
{
    rotation = DOWN;
    matrix.setRotation(DOWN);
}
LEDArray::LEDArray(int dummyPin, int dummyPin2)
{
    rotation = DOWN;
    matrix.setRotation(DOWN);
}

void LEDArray::setup()
{
	matrix.begin(0x70);
	matrix.clear();
	matrix.writeDisplay();
}

void LEDArray::drawHappyFace()
{
    matrix.clear();
    matrix.drawBitmap(0, 0, smile_bmp, 8, 8, LED_ON);
    matrix.writeDisplay();
}

void LEDArray::drawNeutralFace()
{
    matrix.clear();
    matrix.drawBitmap(0, 0, neutral_bmp, 8, 8, LED_ON);
    matrix.writeDisplay();
}

void LEDArray::drawSadFace()
{
    matrix.clear();
    matrix.drawBitmap(0, 0, frown_bmp, 8, 8, LED_ON);
    matrix.writeDisplay();
}

void LEDArray::turnClockwise()
{
    if(rotation == DOWN)
        rotation = LEFT;
    else
        rotation += 1;

    matrix.setRotation(rotation);
}

void LEDArray::turnCounterClockwise()
{
    if(rotation == LEFT)
        rotation = DOWN;
    else
        rotation -= 1;

    matrix.setRotation(rotation);
}

void LEDArray::printText(String text)
{
    matrix.clear();
    matrix.setTextSize(1);
    //false means nice scroll, true means each char appears and then scrolls off
    matrix.setTextWrap(false);
    matrix.setTextColor(LED_ON);

    //negative number of characters * 8
    for (int8_t x=0; x>=-96; x--)
    {
        matrix.clear();
        matrix.setCursor(x,0);
        matrix.print(text);
        matrix.writeDisplay();
        delay(100);
    }
}

void LEDArray::drawPix(int x, int y)
{
    matrix.drawPixel(x, y, LED_ON);
    matrix.writeDisplay();
}

void LEDArray::drawLine(int x1, int y1, int x2, int y2)
{
    matrix.drawLine(x1, y1, x2, y2, LED_ON);
    matrix.writeDisplay();
}

void LEDArray::drawRec(int x1, int y1, int x2, int y2)
{
    matrix.drawRect(x1, y1, x2, y2, LED_ON);
    matrix.writeDisplay();
}

void LEDArray::fillRec(int x1, int y1, int x2, int y2)
{
    matrix.fillRect(x1, y1, x2, y2, LED_ON);
    matrix.writeDisplay();
}

void LEDArray::drawCircle(int x, int y, int r)
{
    matrix.drawCircle(x, y, r, LED_ON);
    matrix.writeDisplay();
}

void LEDArray::clear()
{
    matrix.clear();
    matrix.writeDisplay();
}

void LEDArray::blink(int rate)
{
    matrix.blinkRate(rate);
}

void LEDArray::setBrightness(int level)
{
    matrix.setBrightness(level);
}
