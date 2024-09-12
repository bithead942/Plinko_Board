/*  Star Wars 
Plinko Board
    by Bithead

    This sketch is for an Arduino Uno

    This sketch relies 2 strips of WS2801 RGB LED strands, each with 63 LEDs
    It uses a library called FastLED to control the pixels in the LED strands
    This sketch also relies on 5 Limit Switches

    Pin     Function
    0,1     Serial
    2       Limit Switch 1 - Far Left
    3       Limit Switch 2
    4       Limit Switch 3
    5       Limit Switch 4
    6       Limit Switch 5 - Far Right
    10      Data Pin - right LED Strand
    11      Clock Pin - right LED strand
    12      Data Pin - left LED strand
    13      Clock Pin - left LED strand

 ************************************************************************************/

#include <FastLED.h>

//#define NUMPIXELS 39
#define NUMPIXELS 63
#define DATA_PIN_L 11
#define CLOCK_PIN_L 12
#define DATA_PIN_R 9
#define CLOCK_PIN_R 10
#define Trigger1 2
#define Trigger2 3
#define Trigger3 4
#define Trigger4 5
#define Trigger5 6

uint32_t colorRed = 0xFF0000;
uint32_t colorGreen = 0x00FF00;
uint32_t colorBlue = 0x0000FF;
uint32_t colorOrange = 0xFF2000;
uint32_t colorBlack = 0x000000;  // turn LED off

CRGB leds_L[NUMPIXELS];
CRGB leds_R[NUMPIXELS];

void setup() {

  FastLED.addLeds<WS2801, DATA_PIN_L, CLOCK_PIN_L, RGB>(leds_L, NUMPIXELS);
  FastLED.addLeds<WS2801, DATA_PIN_R, CLOCK_PIN_R, RGB>(leds_R, NUMPIXELS);


  pinMode(Trigger1, INPUT);
  pinMode(Trigger2, INPUT);
  pinMode(Trigger3, INPUT);
  pinMode(Trigger4, INPUT);
  pinMode(Trigger5, INPUT);

  FastLED.setBrightness(130);
  LEDsOff();
}

void loop() {

  if (digitalRead(Trigger1) == HIGH) {  //Far Left
    LEDsChase(10, colorOrange);
  }
  if (digitalRead(Trigger2) == HIGH) {
    LEDsChase(10, colorBlue);
  }
  if (digitalRead(Trigger3) == HIGH) {
    LEDsChaseMulti(10, colorRed, colorBlue);
  }
  if (digitalRead(Trigger4) == HIGH) {
    LEDsChase(10, colorRed);
  }
  if (digitalRead(Trigger5) == HIGH) {  //Far Right
    LEDsChase(10, colorGreen);
  }

  LEDsOff();
  delay(250);
}

void LEDsChase(int cycles, uint32_t color) {
  for (int loop = 0; loop <= cycles; loop++) {
    for (int i = 0; i <= NUMPIXELS; i += 3) {
      leds_L[i] = color;
      leds_L[i + 1] = color;
      leds_L[i + 2] = colorBlack;
      leds_R[i] = color;
      leds_R[i + 1] = color;
      leds_R[i + 2] = colorBlack;
    }
    FastLED.show();
    delay(100);
    for (int i = 0; i <= NUMPIXELS; i += 3) {
      leds_L[i] = colorBlack;
      leds_L[i + 1] = color;
      leds_L[i + 2] = color;
      leds_R[i] = colorBlack;
      leds_R[i + 1] = color;
      leds_R[i + 2] = color;
    }
    FastLED.show();
    delay(100);
    for (int i = 0; i <= NUMPIXELS; i += 3) {
      leds_L[i] = color;
      leds_L[i + 1] = colorBlack;
      leds_L[i + 2] = color;
      leds_R[i] = color;
      leds_R[i + 1] = colorBlack;
      leds_R[i + 2] = color;
    }
    FastLED.show();
    delay(100);
  }
}

void LEDsChaseMulti(int cycles, uint32_t color1, uint32_t color2) {
  for (int loop = 0; loop <= cycles; loop++) {
    for (int i = 0; i <= NUMPIXELS; i += 3) {
      leds_L[i] = color1;
      leds_L[i + 1] = color2;
      leds_L[i + 2] = colorBlack;
      leds_R[i] = color1;
      leds_R[i + 1] = color2;
      leds_R[i + 2] = colorBlack;
    }
    FastLED.show();
    delay(100);
    for (int i = 0; i <= NUMPIXELS; i += 3) {
      leds_L[i] = colorBlack;
      leds_L[i + 1] = color1;
      leds_L[i + 2] = color2;
      leds_R[i] = colorBlack;
      leds_R[i + 1] = color1;
      leds_R[i + 2] = color2;
    }
    FastLED.show();
    delay(100);
    for (int i = 0; i <= NUMPIXELS; i += 3) {
      leds_L[i] = color2;
      leds_L[i + 1] = colorBlack;
      leds_L[i + 2] = color1;
      leds_R[i] = color2;
      leds_R[i + 1] = colorBlack;
      leds_R[i + 2] = color1;
    }
    FastLED.show();
    delay(100);
  }
}

void LEDsOff() {
  for (int i = NUMPIXELS; i >= 0; i--) {
    leds_L[i] = colorBlack;  // 'Off' pixel
    leds_R[i] = colorBlack;  // 'Off' pixel
    FastLED.show();          // Refresh strip
    delay(10);               // Pause 10 milliseconds (~25 FPS)
  }
}
