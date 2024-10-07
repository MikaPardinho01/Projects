/*************************
 * Projeto IOT com ESP32
 * Escola SENAI de Informática
 * Curso de Apredizagem industrial
 * Integrador de soluções em nuvem
 * Data: 01/08/2024
 *
 * Autor: Thiago Augusto de Oliveira
 *
 * Descrição: Projeto de automação utilizando ESP32
 * com conexão WiFi e MQTT.
 *
 * versão: 0.9
 *************************/

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <ArduinoJson.h>
#include "iot.h"
#include "saidas.h"
#include "entradas.h"
#include "tempo.h"
#include "sensores.h"

// Definição dos tópicos de publicação
#define mqtt_pub_topic1 "projeto/sensor/gas"

JsonDocument doc;

// Variáveis globais
unsigned long lastTime = 0;
const unsigned long timerDelay = 1000;

void sensores();
void envia_dados();
void atualiza_display();
void inicializa_display();

void setup()
{
  Serial.begin(115200);
  inicializa_display();
  setup_wifi();
  setup_time();
  inicializa_entradas();
  inicializa_saidas();
  inicializa_mqtt();
  sensores_init();
}

void loop()
{
  atualiza_time();
  atualiza_saidas();
  atualiza_botoes();
  atualiza_mqtt();
  sensores();
  if (millis() - lastTime > timerDelay)
  {
    lastTime = millis();
    envia_dados();
    atualiza_display();
  }
}

void sensores()
{
  float temperatureRead = sensores_get_temperatura();
  float pressureRead = sensores_get_presion();
  float altitudeRead = sensores_get_altitud();
  float humityRead = sensores_get_humity();

  doc["temperature"] = round(temperatureRead * 100.0) / 100.0;
  doc["pressure"] = round(pressureRead * 100.0) / 100.0;
  doc["altitude"] = round(altitudeRead * 100.0) / 100.0;
  doc["humidity"] = round(humityRead * 1.0);
  doc["CO2"] = round(sensores_get_gas() * 100.0) / 100.0;
  doc["timestamp"] = timeStamp();
}

void envia_dados()
{
  String json;
  serializeJson(doc, json);
  publica_mqtt(mqtt_pub_topic1, json);
}