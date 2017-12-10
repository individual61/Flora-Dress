#include <EEPROM.h>
#include <FastLED.h>

#define CORRECTION TypicalLEDStrip
#define LED_PIN 12
#define BACKLED_PIN 8
#define NUM_LEDS 16
#define NUM_BACKLEDS 1
#define BRIGHTNESS 255
#define LED_TYPE WS2811
#define COLOR_ORDER GRB

CRGB leds[NUM_LEDS];
CRGB backled[1];

// CRGB backledcolor = 0x601040;
CRGB backledcolor = 0x000000;
CRGB color = 0x601040;
CRGB starpurple = CRGB(70, 20, 255);
CRGB starpink = CRGB(255, 60, 60);
CRGB starwhite = CRGB(255, 255, 255);

CHSV hsvcolor = CHSV(0, 255, 255);

uint8_t memory = 0;
int address = 0;

int fadeindex = 0;
bool direction = 1;

int offsets[NUM_LEDS];
bool directions[NUM_LEDS];
int fadeindices[NUM_LEDS];

void setup()
{
  Serial.begin(115200);
  for (int j = 0; j < NUM_LEDS; j++)
  {
    directions[j] = 1;
    offsets[j] = random8();
    Serial.println(offsets[j]);
    fadeindices[j] = random8();
  }

  // Change a setting every time it is turned on.
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

  // Set up LEDs
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

  /* Test single colour
    fill_solid(leds, NUM_LEDS, starwhite);
    FastLED.delay(1000);
    */
  for (int j = 0; j < NUM_LEDS; j++)
  {
    if (directions[j] == 1)
    {
      fadeindices[j]++;
    }
    if (directions[j] == 0)
    {
      fadeindices[j]--;
    }
    if (fadeindices[j] == 256)
    {
      directions[j] = !directions[j];
      fadeindices[j] = 255;
    };
    if (fadeindices[j] == -1)
    {
      directions[j] = !directions[j];
      fadeindices[j] = 0;
    };
    float alpha = ((float)((fadeindices[j]) % 256)) / 255.0;
    float omalpha = 1.0 - alpha;
    Serial.print(alpha);
    Serial.print("   ");

    leds[j] = CRGB(alpha * starpurple.red + omalpha * starpink.red,
                   alpha * starpurple.green + omalpha * starpink.green,
                   alpha * starpurple.blue + omalpha * starpink.blue);
    FastLED.delay(1);
  }
  Serial.println();
}
