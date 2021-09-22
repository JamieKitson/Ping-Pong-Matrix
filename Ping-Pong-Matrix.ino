#include <FastLED.h>
#include <FastLED_GFX.h>
#include <LEDMatrix.h>
#include "font.h"

// declare FastLED (matrix / LED strip)
#define LED_PIN        15
#define COLOR_ORDER    GRB
#define CHIPSET        WS2812B

// declare matrix
#define MATRIX_WIDTH   12 // width of matrix
#define MATRIX_HEIGHT  7 // height of matrix
#define MATRIX_TYPE    (MTX_MATRIX_BOTTOM + MTX_MATRIX_LEFT + MTX_MATRIX_COLUMNS + MTX_MATRIX_PROGRESSIVE) // matrix layout flags, add together as needed

// create our matrix based on matrix definition
cLEDMatrix<MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_TYPE> matrix;

void setup() {
  // put your setup code here, to run once:
  
  // initial FastLED by using CRGB led source from our matrix class
  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(matrix[0], matrix.Size());
  FastLED.setBrightness(127);
  FastLED.clear(true);

  matrix.begin();
  matrix.setFont(&TomThumb);
  matrix.print("eo");
  matrix.show();

}

void loop() {
  // put your main code here, to run repeatedly:

}
