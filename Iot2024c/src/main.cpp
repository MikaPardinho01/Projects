#include <Arduino.h>
#include <ArduinoJson.h>
#include "iot.h"
#include "saidas.h"
#include "entradas.h"
#include "tempo.h"
#include "atuadores.h"

// Definição dos tópicos de publicação
#define mqtt_pub_topic1 "projetoProfessor/desafio12"

// Criacao de objetos
const int tokens = 0;

// Variáveis globais
unsigned long tempo_anterior = 0;
const unsigned long intervalo = 5000;

// Prototipo das funcoes

void setup()
{
  Serial.begin(115200);
  setup_wifi();
  setup_time();
  inicializa_entradas();
  inicializa_saidas();
  inicializa_mqtt();
  inicializa_servos();
}

void loop()
{
  atualiza_time();
  atualiza_saidas();
  atualiza_botoes();
  atualiza_mqtt();

  JsonDocument doc;
  String json;
  bool mensagemEmFila = false;

  if (millis() - tempo_anterior >= intervalo)
  {
    tempo_anterior = millis();
    doc["timeStamp"] = timeStamp();
    doc["Token"] = tokens;
    mensagemEmFila = true;
  }

  if (botao_boot_pressionado())
  {
    LedBuiltInState = !LedBuiltInState;
    doc["LedState"] = LedBuiltInState;
    doc["BotaoState"] = true;
    doc["timeStamp"] = timeStamp();
    mensagemEmFila = true;
  }

  else if (botao_boot_solto())
  {
    doc["BotaoState"] = false;
    doc["timeStamp"] = timeStamp();
    mensagemEmFila = true;
  }

  if (mensagemEmFila)
  {
    serializeJson(doc, json);
    publica_mqtt(mqtt_pub_topic1, json);
    mensagemEmFila = false;
  }


}
