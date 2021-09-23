#include <Adafruit_GFX.h>
#include <FastLED_NeoMatrix.h>
#include <FastLED.h>
#include "font.h"
#include <Fonts/Picopixel.h>

const int PIN = 15;

// Padding to allow italic letters into "virtual" space
const int PAD = 4;

const int WIDTH = 12 + PAD;
const int HEIGHT = 7;
const int NUMMATRIX = WIDTH * HEIGHT;

// If the top/bottom edge balls on the same LED column are to the left of the next ball then 1, else 0
const int BALL_DIR = 0;

String message = "This is a longer message.";

CHSV colour( 0, 255, 180);
CRGB leds[NUMMATRIX];

FastLED_NeoMatrix *matrix = new FastLED_NeoMatrix(leds,
  WIDTH, 7,
//  NEO_MATRIX_TOP     + NEO_MATRIX_RIGHT +
  NEO_MATRIX_BOTTOM     + NEO_MATRIX_LEFT +
  NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE
  );

#define arr_len( x )  ( sizeof( x ) / sizeof( *x ) ) // Calculation of Array Size;

const int pixelPerChar = 4;
int counter = WIDTH * 10;

uint16_t myRemapFnTopRight(uint16_t x, uint16_t y) {
  // x = x + ((5 - y) / 2);
  // return (7 * (WIDTH - 1 - x)) + (y % 7);  
}

uint16_t myRemapFnBottomLeft(uint16_t x, uint16_t y) 
{
  x = x - PAD + ((HEIGHT - BALL_DIR - y) / 2);
  return (HEIGHT * x) + (HEIGHT - 1 - y);
}

void setup() {
  FastLED.addLeds<NEOPIXEL, PIN>(  leds, NUMMATRIX  ).setCorrection(TypicalLEDStrip);
  matrix->begin();
  matrix->setFont(&TomThumb);
  matrix->setTextWrap(false);
  matrix->setRemapFunction(myRemapFnBottomLeft);
  matrix->setBrightness(100);
  matrix->setTextColor(CRGB::White);
}

void SetRainbow()
{
  // Difference in hue between neighbouring balls
  const int HUE_JUMP = 10;
  // Speed of rainbow scroll. Negative numbers go counter to text.
  const int HUE_SPEED = 1;
  for ( int column = 0; column < WIDTH; column++)
  {
    for ( int flip = 0; flip < 2; flip++ )
    {
      int offset = BALL_DIR == flip ? 1 : 0;
      for(int row = offset; row < HEIGHT; row += 2)
      {
        int p = (column * HEIGHT) + row;
        leds[p]= colour;
      }
      colour.hue = (colour.hue + HUE_JUMP / 2) % 256;
    }
  }
  colour.hue = (colour.hue - (WIDTH * HUE_JUMP) + HUE_SPEED) % 256;
}

void loop() {

  SetRainbow();

  matrix->setCursor(counter-- / 10, 6); // Set Starting Point for Text String;
  matrix->print(message); // Set the Message String;
  matrix->show();

  int x = message.length() * pixelPerChar * -10;
  if (counter < x)
    counter = WIDTH * 10;

  delay(50);

}
