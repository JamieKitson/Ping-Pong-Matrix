#include <Adafruit_GFX.h>
#include <FastLED_NeoMatrix.h>
#include <FastLED.h>
#include "font.h"

// Padding to allow italic letters into "virtual" space
const int PAD = 4;
const int WIDTH = 12 + PAD;
const int HEIGHT = 7;
const int NUMMATRIX = WIDTH * HEIGHT;

CHSV colour( 0, 255, 180);
CRGB leds[NUMMATRIX];

FastLED_NeoMatrix *matrix = new FastLED_NeoMatrix(leds,
  WIDTH, 7,
//  NEO_MATRIX_TOP     + NEO_MATRIX_RIGHT +
  NEO_MATRIX_BOTTOM     + NEO_MATRIX_LEFT +
  NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE
  );

#define arr_len( x )  ( sizeof( x ) / sizeof( *x ) ) // Calculation of Array Size;

int pixelPerChar = 3;

char msg[] = "This is a longer message.";
int msgSize = arr_len(msg) * (pixelPerChar + 1);

uint16_t myRemapFnTopRight(uint16_t x, uint16_t y) {
  // x = x + ((5 - y) / 2);
  // return (7 * (WIDTH - 1 - x)) + (y % 7);  
}

uint16_t myRemapFnBottomLeft(uint16_t x, uint16_t y) {
  x = x - PAD + ((HEIGHT - y) / 2);
  return (HEIGHT * x) + (HEIGHT - 1 - y);
}

void setup() {
  FastLED.addLeds<NEOPIXEL,15>(  leds, NUMMATRIX  ).setCorrection(TypicalLEDStrip);
  matrix->begin();
  matrix->setFont(&TomThumb);
  //matrix->setTextSize(3);
  matrix->setTextWrap(false);
  matrix->setRemapFunction(myRemapFnBottomLeft);
  matrix->setBrightness(100);
  matrix->setTextColor(CRGB::White);
  matrix->print(msg); // Set the Message String;
  /*
  matrix->print("eo"); // Set the Message String;
  matrix->show();
  delay(1000);
// */
}

int counter = 120;
#define LED_BLACK    0
/*
void RainbowAltPixels(int column, int offset)
{
    for(int j = offset; j < 7; j += 2){
      int p = (column * 7) + j;
      if ((p >= 0) && (p < NUMMATRIX))
      leds[p]= colour;
    }
    colour.hue = (colour.hue + HUE_JUMP / 2) % 256;
}
*/
void loop() {

  const int HUE_JUMP = 20;
  
  for ( int column = 0; column < WIDTH; column++)
  {
    for (int offset = 1; offset >= 0; offset--)
    {
      for(int row = offset; row < HEIGHT; row += 2)
      {
        int p = (column * HEIGHT) + row;
        leds[p]= colour;
      }
      colour.hue = (colour.hue + HUE_JUMP / 2) % 256;
    }
  }
  
  colour.hue = (colour.hue - (WIDTH * HUE_JUMP) + 1) % 256;
  
  matrix->setCursor(counter-- / 10, 6); // Set Starting Point for Text String;
  matrix->print(msg); // Set the Message String;
  matrix->show();
  if (counter / 10 < -msgSize)
    counter = 120;
  delay(50);
  //colour.hue = (colour.hue+1)%256;
}
