/*
 * This project is part of the Movuino demo tutorial from: http://www.movuino.com/
 * Page of the project: http://www.movuino.com/index.php/portfolio/rgb-lamp/
 * Github: https://github.com/hssnadr/RGB-Lamp-Demonstrator
 */

// LED strip
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif
#define pinLed 9                                                                 // Pin controling the led strip behavior
#define nPix 49                                                                  // number of pixels used in the strip
Adafruit_NeoPixel strip = Adafruit_NeoPixel(nPix, pinLed, NEO_GRB + NEO_KHZ800); //   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)

// Auto loop: play random animation before first serial input
bool _isAutoLoop = true;

// RGB values
int stripOrder[] = {0, 1, 2, 3, 4, 5, 6, 7, 9, 8, 10, 11, 12, 14, 13, 15, 16, 17, 21, 20, 19, 18, 22, 28, 27, 26, 25, 24, 23, 29, 30, 32, 31, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48};
boolean isNewColor = false;
byte stripRed[nPix];
byte stripGreen[nPix];
byte stripBlue[nPix];
boolean isColorSet;
int r = 0;
#define r0 4  // led index where letter 'R' starts
#define r1 13 // led index where letter 'R' ends
int g = 0;
#define g0 13 // led index where letter 'G' starts
#define g1 23 // led index where letter 'G' ends
int b = 0;
#define b0 23 // led index where letter 'B' starts
#define b1 34 // led index where letter 'B' ends

long timer0;
long timer1;

// Serial variables
int inByte = 0;    // incoming serial byte
char buffer[40];   // buffer to store incoming bytes
int index = 0;     // current index of the buffer
char msgAdr = 'X'; // address of received messages
int msgVal = -1;   // values of received messages

void setup()
{
  // Serial Port begin
  Serial.begin(9600);

  // LED strip setup
  // strip.setBrightness(50);
  strip.begin(); // This initializes the NeoPixel library.
  strip.show();  // Initialize all pixels to 'off'
  timer0 = millis();
}

void loop()
{
  if (_isAutoLoop)
  {
    autoLoop();
  }
  // Serial.println("HERE");
  HHMM_follower();
  // WheelAnimation();
}

int getTrueLedIndex(int ind_)
{
  // REAL STRIP ORDER
  // to be integrated properly into the lamp, the led strip has been cut and re-solder.
  // I had to modify the order of the led to get the expected effect. This function permits to
  //{1,2,3,4,5,6,7,8,10,9,11,12,13,15,14,16,17,18,22,21,20,19,23,29,28,27,26,25,24,30,31,33,32,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49}
  //       |                        |                             |                             |
  //      red                     green                          blue                          end
  //"RED" = 5 -> 13
  //"GREEN" = 15 -> 23
  //"BLUE" = 29 -> 34

  return stripOrder[ind_];
}
