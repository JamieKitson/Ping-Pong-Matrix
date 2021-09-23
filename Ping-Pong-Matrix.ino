#include <Adafruit_GFX.h>
#include <FastLED_NeoMatrix.h>
#include <FastLED.h>
#include "font.h"
// #include <Fonts/Picopixel.h>
#include <WiFi.h> 
#include <NTPClient.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

const char* ssid = "BT-9ZAKH5";           
const char* password = "k3nRrqEgPmYRAR";

const int PIN = 15;

// Padding to allow italic letters into "virtual" space
const int PAD = 4;

const int WIDTH = 12 + PAD;
const int HEIGHT = 7;
const int NUMMATRIX = WIDTH * HEIGHT;

// If the top/bottom edge balls on the same LED column are to the left of the next ball then 1, else 0
const int BALL_DIR = 0;

// Number of rainbow colour changes for each text pixel move
const int COLOUR_STEPS_TO_TEXT = 5;

String message = "This is a longer message.";

CHSV colour( 0, 255, 180);
CRGB leds[NUMMATRIX];

FastLED_NeoMatrix *matrix = new FastLED_NeoMatrix(leds,
  WIDTH, 7,
//  NEO_MATRIX_TOP     + NEO_MATRIX_RIGHT +
  NEO_MATRIX_BOTTOM     + NEO_MATRIX_LEFT +
  NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE
  );

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);
AsyncWebServer server(80);

#define arr_len( x )  ( sizeof( x ) / sizeof( *x ) ) // Calculation of Array Size;

const int pixelPerChar = 4;
int cursor = WIDTH * 10;
int scrollCount = 0;
bool connected = false;
unsigned long triedConnect;

uint16_t myRemapFnTopRight(uint16_t x, uint16_t y) {
  // x = x + ((5 - y) / 2);
  // return (7 * (WIDTH - 1 - x)) + (y % 7);  
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
  matrix->setFont(&TomThumb);
  matrix->setTextWrap(false);
  matrix->setRemapFunction(myRemapFnBottomLeft);
  matrix->setBrightness(100);
  matrix->setTextColor(CRGB::White);
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
  { 
     if (request->params() > 0)
     {
       AsyncWebParameter* p = request->getParam(0);
       SetMessage(p->value()); // .c_str());
     }
     request->send(200, "text/html", "<meta name=viewport content=\"initial-scale=1.0\" /><form method=get><input type=text name=message><input type=submit></form>");
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

void SetMessage(String msg)
{
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
    message = "WiFi: " + String(WiFi.status());
    scrollCount = 1;
    if ((millis() - triedConnect) / 1000 > 10)
    {
      WiFi.begin(ssid, password);
      triedConnect = millis();
    }
  }
  else if (!connected)
  {
    connected = true;
    SetMessage("Connected");
    timeClient.update();
  }

  if (scrollCount > 0)
    ScrollMessage();
  else
  {
    matrix->setCursor(0, 6);
    matrix->print(timeClient.getFormattedTime());
  }

  matrix->show();

  delay(50);

}
