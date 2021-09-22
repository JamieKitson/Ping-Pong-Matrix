#include <Adafruit_GFX.h>
#include <FastLED_NeoMatrix.h>
#include <FastLED.h>
#include "font.h"

const int PAD = 4;
const int WIDTH = 12 + PAD;
const int HEIGHT = 7;

CHSV colour( 0, 255, 180);
const int NUMMATRIX = WIDTH * HEIGHT;
CRGB leds[NUMMATRIX];

FastLED_NeoMatrix *matrix = new FastLED_NeoMatrix(leds,
  WIDTH, 7,
//  NEO_MATRIX_TOP     + NEO_MATRIX_RIGHT +
  NEO_MATRIX_BOTTOM     + NEO_MATRIX_LEFT +
  NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE
  );

const uint16_t colors[] = {
  matrix->Color(255, 0, 0), matrix->Color(0, 255, 0), matrix->Color(255, 255, 0), matrix->Color(0, 0, 255), matrix->Color(255, 0, 255), matrix->Color(0, 255, 255), matrix->Color(255, 255, 255)
};

#define arr_len( x )  ( sizeof( x ) / sizeof( *x ) ) // Calculation of Array Size;

int pixelPerChar = 3; // Width of Standard Font Characters is 8X6 Pixels

char msg[] = "This is a longer message."; // BLANK Message of Your Choice;
int msgSize = ((sizeof(msg) / sizeof(char)) * (pixelPerChar + 1)); // + (2 * pixelPerChar); // CACULATE message length;

uint16_t myRemapFnTopRight(uint16_t x, uint16_t y) {
  // x = x + ((5 - y) / 2);
  // return (7 * (WIDTH - 1 - x)) + (y % 7);  
}

uint16_t myRemapFnBottomLeft(uint16_t x, uint16_t y) {
  x = x - PAD + ((7 - y) / 2);
  return (7 * x) + ((6 - y) % 7);  
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
const int HUE_JUMP = 30;

void RainbowAltPixels(int offset)
{
    for(int j = offset; j < 7; j += 2){
      int p = (i * 7) + j;
      if ((p >= 0) && (p < NUMMATRIX))
      leds[p]= colour;
    }
    colour.hue = (colour.hue + HUE_JUMP / 2) % 256;
}

void loop() {

  
//  matrix->fillScreen(colour); // BLANK the Entire Screen;
  for ( int i=0; i < WIDTH; i++){
    /*
    for(int j = 0; j < 4; j++){
      int p = ((i / 2) * 7) + (j * 2) + (i %2);
      if ((p >= 0) && (p < NUMMATRIX))
      leds[p]= colour;
    }
    colour.hue = (colour.hue + HUE_JUMP / 2) % 256;
    /* */
    for(int j = 1; j < 7; j += 2){
      int p = (i * 7) + j;
      if ((p >= 0) && (p < NUMMATRIX))
      leds[p]= colour;
    }
    colour.hue = (colour.hue + HUE_JUMP / 2) % 256;
    for(int j = 0; j < 7; j += 2){
      int p = (i * 7) + j;
      if ((p >= 0) && (p < NUMMATRIX))
      leds[p]= colour;
    }
    colour.hue = (colour.hue + HUE_JUMP / 2) % 256;
    // */
  }
  
  colour.hue = (colour.hue - (WIDTH * HUE_JUMP) + 10) % 256;
  
  matrix->setCursor(counter-- / 10, 6); // Set Starting Point for Text String;
  // matrix->print(msg); // Set the Message String;
  matrix->show();
  if (counter / 10 < -msgSize)
    counter = 120;
  delay(50);
  //colour.hue = (colour.hue+1)%256;
}
