#include <FastLED.h>

#define CORRECTION TypicalLEDStrip
#define LED_PIN 12
#define BACKLED_PIN 8
#define NUM_LEDS 16
#define NUM_BACKLEDS 1
#define BRIGHTNESS 255
#define LED_TYPE WS2811
#define COLOR_ORDER GBR

CRGB leds[NUM_LEDS];
CRGB backled[1];

CRGB color = 0x601040;

void setup()
{

  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS)
      .setCorrection(CORRECTION);
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.clear();
  FastLED.show();

  FastLED.addLeds<LED_TYPE, BACKLED_PIN, COLOR_ORDER>(backled, NUM_BACKLEDS)
      .setCorrection(CORRECTION);
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.clear();

  backled[0] = color;

  FastLED.show();
}
int index = 0;
void loop()
{
  index++;
  if (index == NUM_LEDS)
  {
    index = 0;
  };

  leds[index] = CRGB(255, 255, 255);

  FastLED.show();
  FastLED.delay(1000);
  leds[index] = CRGB(0, 0, 0);
  FastLED.show();
}
