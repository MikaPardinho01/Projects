#include <Arduino.h>
#include <FastLED.h>
#include "saidas.h"

const int LED_PIN = 4;
const int NUM_LEDS_TOTAL = 12;

#define BRIGHTNESS 255
#define LED_TYPE WS2811
#define COLOR_ORDER GRB

CRGB leds[NUM_LEDS_TOTAL];

unsigned long intervalo_led = 0;
unsigned long anterior_tempo_led = 1000;
bool isRed = true;

void inicializa_leds()
{
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS_TOTAL);
  FastLED.setBrightness(BRIGHTNESS);
}
void atualiza_leds_branco()
{
  for (int i = 0; i < 4; i++)
  {
    leds[i] = CRGB::White;
  }

  for (int i = 6; i < 10; i++)
  {
    leds[i] = CRGB::White;
  }
}

void atualiza_leds_apagado()
{

  for (int i = 0; i < 4; i++)
  {
    leds[i] = CRGB::Black;
  }

  for (int i = 6; i < 10; i++)
  {
    leds[i] = CRGB::Black;
  }
}

void alterna_cores()
{
  unsigned long currentMillis = millis();

  if (currentMillis - intervalo_led >= anterior_tempo_led)
  {
    intervalo_led = currentMillis;

    if (isRed)
    {
      leds[4] = CRGB::Red;
      leds[5] = CRGB::Yellow;
      leds[10] = CRGB::Red;
      leds[11] = CRGB::Yellow;
    }
    else
    {
      leds[4] = CRGB::Yellow;
      leds[5] = CRGB::Red;
      leds[10] = CRGB::Yellow;
      leds[11] = CRGB::Red;
    }
    isRed = !isRed;
    FastLED.show();
  }
}
