#include <Arduino.h>
#include "Display.h"

int contador = 100;

void setup()
{
  inicializaLCD();
}

void loop()
{
  temporizador(3, contador, 100);
  if (contador > 0)contador --;
  else contador = 100;
  delay(1000);
}
