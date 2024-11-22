#include <Adafruit_NeoPixel.h>

const int LED_PIN = 2;
const int LED_COUNT = 2;
unsigned long interval = 500;
unsigned long timer_anterior = 0;
bool estado = false;

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup()
{
  strip.begin();
  strip.show();
}

 void loop()
{
  unsigned long tempo_atual = millis();

  uint32_t yellow = strip.Color(255, 255, 0);
  uint32_t red = strip.Color(255, 0, 0);
  uint32_t off = strip.Color(0, 0, 0);

  if (tempo_atual - timer_anterior >= interval)
  {
    timer_anterior = tempo_atual;
    if (estado)
    {
      strip.setPixelColor(0, off);
      strip.setPixelColor(1, red);

      strip.show();
      strip.setPixelColor(0, red);
      strip.setPixelColor(1, off);
      strip.show();

      strip.setPixelColor(0, off);
      strip.setPixelColor(1, yellow);
      strip.show();
    }

    estado !=estado;
    strip.show();
  }
}
