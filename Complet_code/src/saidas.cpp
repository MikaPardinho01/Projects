#include <Arduino.h>
#include <Adafruit_NeoPixel.h>


const int Led_central = 6;
const int led_sinal = 4;
const int num_sinal = 2;
const int NUM_LEDS = 6; 
const int BRIGHTNESS = 255;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, Led_central, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip_sinal = Adafruit_NeoPixel(num_sinal, led_sinal, NEO_GRB + NEO_KHZ800);

unsigned long previous = 0;
bool alterando = true;

void inicializa_leds()
{
  strip.begin();
  strip.setBrightness(BRIGHTNESS);
  strip_sinal.begin();
  strip_sinal.setBrightness(255);
  strip_sinal.setPixelColor(0, strip_sinal.Color(255, 0, 0)); 
  strip_sinal.show();
}

void atualiza_sinais()
{
  unsigned long current = millis();
  if (current - previous >= 500)
  {
    previous = current;

    if (alterando)
    {
      strip_sinal.setPixelColor(0, strip_sinal.Color(255, 255, 0)); 
      strip_sinal.setPixelColor(1, strip_sinal.Color(255, 0, 0));   
    }
    else
    {
      strip_sinal.setPixelColor(0, strip_sinal.Color(255, 0, 0));   
      strip_sinal.setPixelColor(1, strip_sinal.Color(255, 255, 0)); 
    }
    strip_sinal.show(); 
    alterando = !alterando; 
  }
}

void setColors(uint32_t color1, uint32_t color2)
{
  strip.setPixelColor(0, color1);
  strip.setPixelColor(1, color2);
  strip.show();
}


void setWhiteColor()
{
  for (int i = 0; i < NUM_LEDS; i++)
  {
    strip.setPixelColor(i, strip.Color(255, 255, 255)); 
  }
  strip.show();
}

