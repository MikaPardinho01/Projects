#include <Arduino.h>
#include <ArduinoJson.h>
#include "json.h"
#include "iot.h"
#include "tempo.h"
#include "saidas.h"
#include "entradas.h"
#include "atuadores.h"
#include "temperatura.h"
#include "display.h"
#include "nfc_rfid.h"
#include "sensor.Gas.h"
#include "motor.h"

#define mqtt_topic1 "projeto_auto_factory"

unsigned long time_anterior = 0;
unsigned long time_definido = 1000;
const int resposta = 0;

void inicializa_json()
{
    JsonDocument doc;
    String json;
    bool mensagemEmFila = false;

    if (millis() - time_anterior >= time_definido)
    {
        time_anterior = millis();
        doc["timeStamp"] = timeStamp();
        doc["UIDCadastrado"] = numericUID;
        doc["UIDarmazenadoposicao"] = i_posicao;
        doc["UIDDetectado"] = duplicado;
        doc["Temperatura"] = temperatura;
        doc["Umidade"] = humidade;
        doc["CO2"] = round(sensores_get_gas() * 100.0) / 100.0;
        mensagemEmFila = true;
    }
   else if (botao_externo_pressionado())
    {
        LuzCentral = !LuzCentral;
        doc["LedState"] = LuzCentral;
        doc["BotaoState"] = true;
        mensagemEmFila = true;
    }
    else if (botao_externo_solto())
    {
        doc["BotaoState"] = false;
        mensagemEmFila = true;
    }
    else if (botao_servo_pressionado())
    {
        doc["PortaoState"] = angulo_servo;
        doc["BotaoservoState"] = actionState;
        if (actionState)
        { 
            angulo_servo = 180;
            Serial.println("Servo ligado");
        }
        else 
        {
            angulo_servo = 0;
        }
        posiciona_servo(angulo_servo);
        mensagemEmFila = true;
    }
    if (mensagemEmFila)
    {
        serializeJson(doc, json);
        publica_mqtt(mqtt_topic1, json);
        mensagemEmFila = false;
    }
}
