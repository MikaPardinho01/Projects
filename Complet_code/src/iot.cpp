#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <TimeLib.h>
#include <WiFiClientSecure.h>
#include "iot.h"
#include "senhas.h"
#include "saidas.h"
#include "json.h"
#include "atuadores.h"
#include "entradas.h"
#include "nfc_rfid.h"
#include "memory.h"
#include "motor.h"
#include "token.h"

// Definição dos tópicos de inscrição
#define mqtt_topic1 "projeto_auto_factory"

#define USUARIO_PADRAO "!@#$%^&*()xyz"

// Definição do ID do cliente MQTT randomico
const String cliente_id = "ESP32Client" + String(random(0xffff), HEX);

String usuarioAutorizado = USUARIO_PADRAO;

// Protótipos das funções
void tratar_msg(char *topic, String msg);
void callback(char *topic, byte *payload, unsigned int length);
void reconecta_mqtt();
void inscricao_topicos();

// Definição dos dados de conexão

WiFiClientSecure espClient;
PubSubClient client(AWS_IOT_ENDPOINT, mqtt_port, callback, espClient);

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

  espClient.setCACert(AWS_CERT_CA);
  espClient.setCertificate(AWS_CERT_CRT);
  espClient.setPrivateKey(AWS_CERT_PRIVATE);
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

  tratar_msg(topic, msg);
}

// Função de reconexão ao Broker MQTT
void reconecta_mqtt()
{
  while (!client.connected())
  {
    Serial.print("Tentando se conectar ao Broker MQTT: ");
    Serial.println(AWS_IOT_ENDPOINT);
    if (client.connect(THINGNAME))
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
  client.subscribe(mqtt_topic1);
}

// Trata as mensagens recebidas
void tratar_msg(char *topic, String msg)
{
    //   int senha = randomiza_senha();

    // JsonDocument doc;
    // deserializeJson(doc, msg);
    // if (doc.containsKey("token"))
    // {
    //   if (doc["token"] == senha)
    //   {
    //     if (doc.containsKey("user"))
    //     {
    //       String user = doc["user"];

    //       if (usuarioAutorizado == USUARIO_PADRAO) 
    //         usuarioAutorizado = user; 

    //       if (usuarioAutorizado == user) 
    //       {
    //         mostrarTempoRestante(); 

    //         //! ******** USUARIO AUTORIZADO APARTIR DAQUI ***********/
    //         // if (doc.containsKey("LedState"))
    //         // {
    //         //   LedBuiltInState = doc["LedState"];
    //         // }

    //         //! ******** USUARIO AUTORIZADO ATÉ AQUI ***********/
    //       }
    //     }
    //   }
    // }
  if (strcmp(topic, mqtt_topic1) == 0)
  {
    JsonDocument doc;
    deserializeJson(doc, msg);
    if (doc.containsKey("BotaoservoState"))
    {
      servoPowerState = doc["BotaoservoState"];

      if (servoPowerState)
      {
        angulo_estoque = 90;
      }
      else
      {
        angulo_estoque = 0;
      }
      posiciona_servo_estoque(angulo_estoque);
    }
  }
  if (strcmp(topic, mqtt_topic1) == 0)
  {
    JsonDocument doc;
    deserializeJson(doc, msg);
    if (doc.containsKey("PortaoState"))
    {
      actionState = doc["PortaoState"];

      if (actionState)
      {
        angulo_despache = 90;
      }
      else
      {
        angulo_despache = 0;
      }
      posiciona_servo_despache(angulo_despache);
    }
  }
  // if (strcmp(topic, mqtt_topic1) == 0) {
  //   JsonDocument doc;
  //   deserializeJson(doc, msg);
  //   if (doc.containsKey("motorState"))
  //   {
  //     motorPowerState = doc["motorState"];
  //     if (motorPowerState > 3)
  //      motorPowerState++;
  //     {
  //       switch (motorPowerState)
  //       {
  //       case 0:
  //         analogWrite(motorPin, 0);
  //         break;
  //       case 1:
  //         analogWrite(motorPin, 85);
  //         break;
  //       case 2:
  //         analogWrite(motorPin, 170);
  //         break;
  //       case 3:
  //         analogWrite(motorPin, 255);
  //         break;
  //       }
  //     }
  //   }
  // }
  if (strcmp(topic, mqtt_topic1) == 0)
  {
    JsonDocument doc;
    deserializeJson(doc, msg);
    if (doc.containsKey("ledState"))
    {
      ledPowerState = doc["ledState"];
      if (ledPowerState)
      {
        atualiza_leds_branco();
      }
      else
      {
        atualiza_leds_apagado();
      }
    }
  }
}