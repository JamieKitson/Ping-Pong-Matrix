#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#include "font.h"

const int PAD = 4;
const int WIDTH = 12 + PAD;

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(WIDTH, 7, 15,
//  NEO_MATRIX_TOP     + NEO_MATRIX_RIGHT +
  NEO_MATRIX_BOTTOM     + NEO_MATRIX_LEFT +
  NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE,
  NEO_GRB            + NEO_KHZ800);

const uint16_t colors[] = {
  matrix.Color(255, 0, 0), matrix.Color(0, 255, 0), matrix.Color(255, 255, 0), matrix.Color(0, 0, 255), matrix.Color(255, 0, 255), matrix.Color(0, 255, 255), matrix.Color(255, 255, 255)
};

#define arr_len( x )  ( sizeof( x ) / sizeof( *x ) ) // Calculation of Array Size;

int pixelPerChar = 3; // Width of Standard Font Characters is 8X6 Pixels
int x = matrix.width(); // Width of the Display
int pass = 0; // Counter
int i = 0; // Counter
int clr = 0; // Counter for Indexing Array of Colors

char msg[] = "1rstuvwxyz"; // BLANK Message of Your Choice;
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
  matrix.begin();
  matrix.setFont(&TomThumb);
  //matrix.setTextSize(3);
  matrix.setTextWrap(false);
  matrix.setRemapFunction(myRemapFnBottomLeft);
  matrix.setBrightness(100);
  matrix.setTextColor(colors[0]);
  /*
  matrix.print("eo"); // Set the Message String;
  matrix.show();
*/
}

int counter = 8;

void loop() {

  matrix.fillScreen(0); // BLANK the Entire Screen;
  matrix.setTextColor(colors[0]);
  matrix.setCursor(counter--, 6); // Set Starting Point for Text String;
  matrix.print(msg); // Set the Message String;
  matrix.show();
  if (counter < -msgSize)
    counter = 4;
  delay(1000);
  
/*
  int arrSize = arr_len( colors );
  char exampleText[] = "Happy Birthday James!"; // SCROLLING Message of Your Choice;
  writeText(exampleText);
  delay(1000);

  matrix.print(msg); //Print the Message String;
  matrix.show();
  delay(1000);

  //  Commands for Debugging  
  char msgText[] = "Let's Start Over";
  matrix.print(msgText); // Scrolling Print the Message String;
  matrix.show();
  delay(1000);
 
  writeText("End of Loop"); //Print the Message String;
  delay(1000);
  //  Commands for Debugging  
 
  // LATHER - RINSE - REPEAT Is Why coders never leave the Shower;
  */
}

/* --------------------  FUNCTIONS BELOW  --------------------  */
void writeText(String msg) {
  int arrSize = arr_len( colors ); // Array of Text Colors;
  int msgSize = (msg.length() * pixelPerChar) + (2 * pixelPerChar); // CACULATE message length;
  int scrollingMax = (msgSize) + matrix.width(); // ADJUST Displacement for message length;

  x = matrix.width(); // RESET Cursor Position and Start Text String at New Position on the Far Right;
  clr = 0; // RESET Color/Repeat Index;

  while (clr <= arrSize) {
    /* Change Color with Each Pass of Complete Message */
    matrix.setTextColor(colors[clr]);

    matrix.fillScreen(0); // BLANK the Entire Screen;
    matrix.setCursor(x, 0); // Set Starting Point for Text String;
    matrix.print(msg); // Set the Message String;

    /* SCROLL TEXT FROM RIGHT TO LEFT BY MOVING THE CURSOR POSITION */
    if (--x < -scrollingMax ) {
      /*  ADJUST FOR MESSAGE LENGTH  */
      // Decrement x by One AND Compare New Value of x to -scrollingMax;
     // This Animates (moves) the text by one pixel to the Left;

      x = matrix.width(); // After Scrolling by scrollingMax pixels, RESET Cursor Position and Start String at New Position on the Far Right;
      ++clr; // INCREMENT COLOR/REPEAT LOOP COUNTER AFTER MESSAGE COMPLETED;
    }
    matrix.show(); // DISPLAY the Text/Image
    delay(500); // SPEED OF SCROLLING or FRAME RATE;
  }
  clr = 0; // Reset Color/Loop Counter;

/* LATHER - RINSE - REPEAT - Why coders have such nice hair */
}
