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


const int NUM_LEDS_MAIN = 4;  
const int NUM_LEDS_COLOR = 8; 
const int COLOR_START_INDEX = NUM_LEDS_MAIN; 

void inicializa_leds()
{
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS_TOTAL);
  FastLED.setBrightness(BRIGHTNESS);
  atualiza_apagado();
}

void atualiza_branco()
{
  for (int i = 0; i < NUM_LEDS_MAIN; i++)
  {
    leds[i] = CRGB::White;
  }
  FastLED.show();
}

void atualiza_apagado()
{
  for (int i = 0; i < NUM_LEDS_MAIN; i++)
  {
    leds[i] = CRGB::Black;
  }
  FastLED.show();
}

void inicializa_leds_color()
{
  for (int i = COLOR_START_INDEX; i < NUM_LEDS_TOTAL; i++)
  {
    leds[i] = CRGB::Red;
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
      leds[COLOR_START_INDEX] = CRGB::Red;
      leds[COLOR_START_INDEX + 1] = CRGB::Yellow;
    }
    else
    {
      leds[COLOR_START_INDEX] = CRGB::Yellow;
      leds[COLOR_START_INDEX + 1] = CRGB::Red;
    }

    isRed = !isRed;
    FastLED.show();
  }
}
