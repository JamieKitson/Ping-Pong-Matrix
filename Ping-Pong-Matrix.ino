#include <Adafruit_GFX.h>
#include <FastLED_NeoMatrix.h>
#include <FastLED.h>
#include "font.h"
// #include <Fonts/Picopixel.h>
#include <WiFi.h> 
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ezTime.h>

const char* ssid = "BT-9ZAKH5";           
const char* password = "k3nRrqEgPmYRAR";

const int PIN = 15;

// Padding to allow italic letters into "virtual" space
const int PAD = 4;

const int WIDTH = 17 + PAD;
const int HEIGHT = 7;
const int NUMMATRIX = WIDTH * HEIGHT;

// If the top/bottom edge balls on the same LED column are to the left of the next ball then 1, else 0
const int BALL_DIR = 0;

// Number of rainbow colour changes for each text pixel move
const int COLOUR_STEPS_TO_TEXT = 5;

String message;

CHSV colour( 0, 255, 180);
CRGB leds[NUMMATRIX];

FastLED_NeoMatrix *matrix = new FastLED_NeoMatrix(leds,
  WIDTH, 7,
//  NEO_MATRIX_TOP     + NEO_MATRIX_RIGHT +
  NEO_MATRIX_BOTTOM     + NEO_MATRIX_LEFT +
  NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE
  );

Timezone timeZone;
AsyncWebServer server(80);
  
const int pixelPerChar = 4;
int cursor = WIDTH * 10;
int scrollCount = 0;
bool connected = false;
unsigned long triedConnect;
int lightReading = 2000;

const int Digits[10][10] =
{
  {7,8,10,11,14,18,22,24},
  {14,16,18,15,17},
//  {14,16,18,22,24},
  {7,8,9,11,14,16,18,24},
  {7,9,11,14,16,18,22,24},
  {9,10,11,16,18,22,24},
  {7,9,10,11,14,16,18,22},
  {7,8,9,14,15,16,18,22},
  {7,11,14,16,17,24},
  {7,8,9,10,11,14,16,18,22,24},
  {7,9,10,11,14,16,17,24},
};

int invertAlternateColumns(int pos)
{
      if (((pos / 7) % 2) == 1)
      {
        pos = pos - (pos % 7) + (6 - pos % 7);
      }
      if (((pos % 7) % 2) == 1)
      {
        pos += 7;
      }
      return pos;
}

void displaynumber( int place , int number){
  for (int i = 0 ; i < 10 ; i++) {
    int first = number/10; 
    if (Digits[first][i] != 0) {
      int pos = Digits[first][i] + place;
      pos = invertAlternateColumns(pos);
      /*
      if (((pos / 7) % 2) == 1)
      {
        pos = pos - (pos % 7) + (6 - pos % 7);
      }
      */
      leds[pos] = CRGB(255,255,255);;
    }
    int sec = number%10;
    if (Digits[sec][i] != 0) {
      int pos = Digits[sec][i]+28+place;
      pos = invertAlternateColumns(pos);
      leds[pos] = CRGB(255,255,255);;
    }
  }
}

uint16_t myRemapFnTopRight(uint16_t x, uint16_t y) {
  // x = x + ((5 - y) / 2);
  return (7 * (WIDTH - 1 - x)) + (y % 7);  
}

uint16_t myRemapFnBottomLeft(uint16_t x, uint16_t y) 
{
  x = x - PAD + ((HEIGHT - BALL_DIR - y) / 2);
  return (HEIGHT * x) + (HEIGHT - 1 - y);
}

void setup() 
{
  WiFi.begin(ssid, password);
  triedConnect = millis();
  FastLED.addLeds<NEOPIXEL, PIN>(  leds, NUMMATRIX  ).setCorrection(TypicalLEDStrip);
  matrix->begin();
//  matrix->setFont(&TomThumb);
  matrix->setTextWrap(false);
//  matrix->setRemapFunction(myRemapFnBottomLeft);
  matrix->setBrightness(100);
  matrix->setTextColor(CRGB::White);
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
  { 
     if (request->params() > 0)
     {
       AsyncWebParameter* p = request->getParam(0);
       SetMessage(p->value());
     }
     request->send(200, F("text/html"), F("<meta name=viewport content=\"initial-scale=1.0\" /><form method=get><input type=text name=message><input type=submit></form>"));
  });
  server.begin();
}

void SetRainbow()
{
  // Difference in hue between neighbouring balls
  const int HUE_JUMP = 10;
  // Speed of rainbow scroll. Negative numbers go cursor to text.
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

void ScrollMessage()
{
  matrix->setCursor(cursor-- / COLOUR_STEPS_TO_TEXT, 6);
  matrix->print(message);

  int x = - message.length() * pixelPerChar * COLOUR_STEPS_TO_TEXT;
  if (cursor < x)
  {
    cursor = WIDTH * COLOUR_STEPS_TO_TEXT;
    scrollCount--;
  }
}

void SetMessage(const String& msg)
{
  matrix->setFont(&TomThumb);
  matrix->setRemapFunction(myRemapFnBottomLeft);
  
  message = msg;
  cursor = WIDTH * COLOUR_STEPS_TO_TEXT;
  scrollCount = 2;
}

void loop() 
{

  SetRainbow();

  if (WiFi.status() != WL_CONNECTED)
  {
    connected = false;
    message = "WiFi: ";
    message =+ WiFi.status();
    scrollCount = 1;
    if ((millis() - triedConnect) / 1000 > 10)
    {
      WiFi.begin(ssid, password);
      triedConnect = millis();
    }
  }
  else if (!connected)
  {
    // message = "Connected";
    connected = true;
    timeZone.setLocation(F("Europe/London"));
    updateNTP();
    scrollCount = 0;
  }

  const int STEPS = 30;
  int lightDiff = analogRead(34) - lightReading;
  int absLightDiff = abs(lightDiff);
  if ((lightDiff != 0) && (absLightDiff < STEPS))
    lightDiff = (lightDiff / absLightDiff) * STEPS;
    
  // Don't jump immediately to new brightness, do it in steps
  lightReading = lightReading + lightDiff / STEPS;
  matrix->setBrightness(map(lightReading, 0, 4096, 50, 255));

//  message = lightReading;
//  scrollCount = 1;

  if (scrollCount > 0)
    ScrollMessage();
  else
  {
      displaynumber(-6,timeZone.minute());
  displaynumber(64,timeZone.second());
      if ( timeZone.second() % 2 == 0 ){
    leds[58] = CRGB(255,255,255);
    leds[60] = CRGB(255,255,255);
  }
    /*
  matrix->setFont(&TomThumb);
  matrix->setRemapFunction();
    matrix->setCursor(3, 6);
    matrix->print(timeZone.dateTime(F("H:i")));
    */
  }

  matrix->show();

  delay(50);

}
