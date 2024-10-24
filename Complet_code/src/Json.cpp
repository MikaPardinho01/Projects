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
#define mqtt_topic2 "ProjetoKaue/receba"

// Definição do ID do cliente MQTT randomico
const String cliente_id = "ESP32Client" + String(random(0xffff), HEX);

// Definicao para o token
const int Tokens = 1803;
String resposta = "Sim";

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
    client.subscribe(mqtt_topic1); // LED 2
}

// Trata as mensagens recebidas
void tratar_msg(char *topic, String msg)
{
    if (strcmp(topic, mqtt_topic1) == 0)
    {
        JsonDocument doc;
        deserializeJson(doc, msg);
        if (doc.containsKey("BotaoservoState"))
        {
            actionState = doc["BotaoservoState"];

            if (actionState)
            {
                angulo_servo = 180;
            }

            else
            {
                angulo_servo = 0;
            }
            posiciona_servo(angulo_servo);
        }
    }
    if (strcmp(topic, mqtt_topic2) == 0)
    {
        JsonDocument doc;
        deserializeJson(doc, msg);

        if (doc.containsKey("MudaSenha"))
        {
            unsigned long novoIntervalo = doc["MudaSenha"];
            Intervalo_Normal = novoIntervalo;
            Serial.println("----------------------");
            Serial.print("\nIntervalo de tempo: ");
            Serial.println(Intervalo_Normal / 1000);
            // preferences.putULong("Intervalo", Intervalo_Normal); // Salvar o valor na memória
        }

        if (doc.containsKey("TempoExtra"))
        {
            unsigned long SenhaTravada = doc["TempoExtra"];
            Tempo_extra = SenhaTravada;
            Serial.print("\nTempo extra: ");
            Serial.println(Tempo_extra / 1000);
            Serial.println("----------------------");
            // preferences.putULong("TempoExtra", Tempo_extra);
        }
    }
}
