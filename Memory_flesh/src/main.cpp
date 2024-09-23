#include <Arduino.h>
#include <Bounce2.h>
#include <Preferences.h>

#define BUTTON_PIN 0

Bounce botao = Bounce();
Preferences preferences;

int contador = 0;

void setup()
{
  botao.attach(BUTTON_PIN, INPUT_PULLUP);
  Serial.begin(9600);
  preferences.begin("config", false);
  contador = preferences.getInt("contador", 0);
  Serial.printf("Contagem inicia em: %d \n\r", contador);
}

void loop()
{

  botao.update();
  if (botao.rose())
  {

    if (botao.previousDuration() > 3000)
    {
      contador = 0;
      preferences.putInt("contador", contador);
    }
    else

      contador++;                                
    preferences.putInt("contador", contador);    
    Serial.printf("Contagem: %d \n\r", contador);
  }
}
