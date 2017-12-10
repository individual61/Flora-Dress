#include <EEPROM.h>
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

CRGB backledcolor = 0x601040;
CRGB color = 0x601040;
CHSV hsvcolor = CHSV(0, 255, 255);

uint8_t memory = 0;
int address = 0;

void setup()
{
  memory = EEPROM.read(address);
  memory++;
  if (memory == 2)
  {
    memory = 0;
  }
  EEPROM.write(address, memory);
  if (memory == 0)
  {
    color = 0xFF0000;
  }
  if (memory == 1)
  {
    color = 0x0000FF;
  }

  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS)
      .setCorrection(CORRECTION);
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.clear();
  FastLED.show();

  FastLED.addLeds<LED_TYPE, BACKLED_PIN, COLOR_ORDER>(backled, NUM_BACKLEDS)
      .setCorrection(CORRECTION);
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.clear();

  backled[0] = backledcolor;

  FastLED.show();
}
int index = 0;
void loop()
{
  /*
// Turn on each separately white for one second
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
  */

  /*
    // Cycle all through wheel
    index++;
    if (index == 255)
    {
      index = 0;
    };
    hsvcolor = CHSV(index, 255, 255);
    fill_solid(leds, NUM_LEDS, hsvcolor);
    FastLED.delay(20);
  */

  /*
    // Each powerup use different color
    fill_solid(leds, NUM_LEDS, color);
    FastLED.delay(1000);
    */

  fill_solid(leds, NUM_LEDS, color);
  FastLED.delay(1000);
}
