#include <FastLED.h>
#include "saidas.h"

const int LED_PIN = 4;
const int NUM_LEDS = 2;
const int LED_PIN_COLOR = 18;
const int NUM_LEDS_COLOR = 2;

#define BRIGHTNESS 255
#define LED_TYPE WS2811
#define COLOR_ORDER GRB

CRGB leds[NUM_LEDS];
CRGB leds_color[NUM_LEDS_COLOR];

unsigned long intervalo_led = 0;
unsigned long anterior_tempo_led = 1000;
bool isRed = true;

void inicializa_leds()
{
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  atualiza_apagado();
}

void inicializa_leds_color()
{
  FastLED.addLeds<LED_TYPE, LED_PIN_COLOR, COLOR_ORDER>(leds_color, NUM_LEDS_COLOR);
  FastLED.setBrightness(BRIGHTNESS);
  for (int i = 0; i < NUM_LEDS_COLOR; i++)
  {
    leds_color[i] = CRGB::Red;
  }
  FastLED.show();
}
void atualiza_branco()
{
  for (int i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = CRGB::White;
  }
  FastLED.show();
}

void atualiza_apagado()
{
  for (int i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = CRGB::Black;
  }
  FastLED.show();
}

void atualiza_leds_color()
{
  unsigned long currentMillis = millis();
  if (currentMillis - intervalo_led >= anterior_tempo_led)
  {
    intervalo_led = currentMillis;
    if (isRed)
    {
      leds_color[0] = CRGB::Red;
      leds_color[1] = CRGB::Yellow;
    }

    else
    {
      leds_color[0] = CRGB::Yellow;
      leds_color[1] = CRGB::Red;
    }

    isRed = !isRed;
    FastLED.show();
  }
}
