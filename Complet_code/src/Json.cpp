#include <Arduino.h>
#include <ArduinoJson.h>
#include "json.h"
#include "iot.h"
#include "tempo.h"
#include "saidas.h"
#include "entradas.h"
#include "totem.h"
#include "atuadores.h"

#define mqtt_topic1 "projeto_auto_factory"
int angulo = map(analogRead(A0), 0, 4095, 0, 180);

unsigned long tempo_anterior = 0;
const unsigned long intervalo = 1000;
const int resposta = 0;

void inicializa_json()
{
    JsonDocument doc;
    String json;
    bool mensagemEmFila = false;

    if (millis() - tempo_anterior >= intervalo)
    {
        tempo_anterior = millis();
        doc["timeStamp"] = timeStamp();
        doc["Token"] = resposta;
        mensagemEmFila = true;
    }
    if (botao_externo_pressionado())
    {
        LuzCentral = !LuzCentral;
        doc["LedState"] = LuzCentral;
        doc["BotaoState"] = true;
        doc["timeStamp"] = timeStamp();
        mensagemEmFila = true;
    }
    else if (botao_externo_solto())
    {
        doc["BotaoState"] = false;
        doc["timeStamp"] = timeStamp();
        mensagemEmFila = true;
    }
    else if (posiciona_servo())
    {
        doc["PortaoState"] = angulo;
        serializeJson(doc, json);
        publica_mqtt(mqtt_topic1, json);
    }

    if (mensagemEmFila)
    {
        serializeJson(doc, json);
        publica_mqtt(mqtt_topic1, json);
        mensagemEmFila = false;
    }
}
