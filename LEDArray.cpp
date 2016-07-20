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
