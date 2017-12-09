#include <FastLED.h>

#define CORRECTION TypicalLEDStrip
#define LED_PIN 12
#define NUM_LEDS 16
#define BRIGHTNESS 255
#define LED_TYPE WS2811
#define COLOR_ORDER GBR

CRGB leds[NUM_LEDS];

CRGB color = 0x601040;

void setup()
{

  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS)
      .setCorrection(CORRECTION);
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.clear();
  FastLED.show();
}

void loop()
{

  leds[0] = CRGB(255, 0, 0);
  leds[1] = CRGB(0, 255, 0);
  leds[2] = CRGB(0, 0, 255);
  FastLED.show();
  FastLED.delay(1000);
}
