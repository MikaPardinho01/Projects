#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <TimeLib.h>
#include "iot.h"
#include "senhas.h"
#include "saidas.h"
#include "atuadores.h"

// Definição dos tópicos de inscrição
#define mqtt_topic2 "projetoProfessor/desafio12"

// Definição do ID do cliente MQTT randomico
const String cliente_id = "ESP32Client" + String(random(0xffff), HEX);

// Definição do token correto
const int correctToken = 1803;

// Definição dos dados de conexão
WiFiClient espClient;
PubSubClient client(espClient);

// Protótipos das funções
void tratar_msg(char *topic, String msg);
void callback(char *topic, byte *payload, unsigned int length);
void reconecta_mqtt();
void inscricao_topicos();

// Inicia a conexão WiFi
void setup_wifi()
{
  Serial.println();
  Serial.print("Conectando-se a Rede WiFi ");
  Serial.print(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Conectado ao WiFi com sucesso com IP: ");
  Serial.println(WiFi.localIP());
}

// Inicia a conexão MQTT
void inicializa_mqtt()
{
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}

// Atualiza a conexão MQTT
void atualiza_mqtt()
{
  client.loop();
  if (!client.connected())
  {
    reconecta_mqtt();
  }
}

// Função de callback chamada quando uma mensagem é recebida
void callback(char *topic, byte *payload, unsigned int length)
{
  String msg = "";
  for (int i = 0; i < length; i++)
  {
    msg += (char)payload[i];
  }

  // Serial.printf("Mensagem recebida em [ %s ] \n\r", topic);
  // Serial.printf(msg);

  tratar_msg(topic, msg);
}

// Função de reconexão ao Broker MQTT
void reconecta_mqtt()
{
  while (!client.connected())
  {
    Serial.print("Tentando se conectar ao Broker MQTT: ");
    Serial.println(mqtt_server);
    if (client.connect(cliente_id.c_str()))
    {
      Serial.println("Conectado ao Broker MQTT");
      inscricao_topicos();
    }
    else
    {
      Serial.println("Falha ao conectar ao Broker.");
      Serial.println("Havera nova tentativa de conexao em 2 segundos");
      delay(2000);
    }
  }
}

// Publica uma mensagem no tópico MQTT
void publica_mqtt(String topico, String msg)
{
  client.publish(topico.c_str(), msg.c_str());
}

// Inscreve nos tópicos MQTT
void inscricao_topicos()
{
  client.subscribe(mqtt_topic2); // Inscreve no tópico definido
}

// Trata as mensagens recebidas
void tratar_msg(char *topic, String msg)
{
  if (strcmp(topic, mqtt_topic2) == 0)
  {
    // Analisa a mensagem como JSON
    DynamicJsonDocument doc(1024);
    DeserializationError error = deserializeJson(doc, msg);
    if (error)
    {
      Serial.print("Falha na desserialização JSON: ");
      Serial.println(error.c_str());
      return;
    }

    // Verifica se a mensagem contém o campo Token e LedState
    if (doc.containsKey("Token") && doc.containsKey("LedState"))
    {
      int receivedToken = doc["Token"].as<int>();
      bool ledState = doc["LedState"].as<bool>();

      // Verifica se o token está correto
      if (receivedToken == correctToken)
      {
        // Atualiza o estado do LED conforme a mensagem
        LedBuiltInState = ledState;
        digitalWrite(LED_BUILTIN, LedBuiltInState ? HIGH : LOW); // Liga ou desliga o LED
        Serial.println("Token correto. LED atualizado.");
      }
      else
      {
        Serial.println("Token incorreto. LED não alterado.");
      }
    }
    else
    {
      Serial.println("Mensagem JSON inválida.");
    }
  }
}

void setup()
{
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT); // Configura o pino do LED como saída

  setup_wifi();
  inicializa_mqtt();
}

void loop()
{
  atualiza_mqtt();
}
