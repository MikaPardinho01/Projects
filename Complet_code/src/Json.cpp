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
#define mqtt_topic2 "ProjetoKaue/receba"

unsigned long time_anterior = 0;
const unsigned long time_definido = 1000;

void inicializa_json()
{
    JsonDocument doc;
    String json;
    bool mensagemEmFila = false;

    if (millis() - time_anterior >= time_definido)
    {
        time_anterior = millis();
        doc["timeStamp"] = timeStamp();
        doc["UID_Cadastrado: "] = numericUID;
        doc["UID_armazenado_posicao: "] = i_posicao;
        doc["UID_detectado"] = duplicado;
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
        doc["timeStamp"] = timeStamp();
        mensagemEmFila = true;
    }
    else if (botao_externo_solto())
    {
        doc["BotaoState"] = false;
        doc["timeStamp"] = timeStamp();
        mensagemEmFila = true;
    }
    else if (botao_servo_pressionado())
    {
        doc["PortaoState"] = angulo_servo;
        doc["BotaoservoState"] = actionState;
        if (actionState)
        {
            angulo_servo = 180;
        }
        else
        {
            angulo_servo = 0;
        }
        posiciona_servo(angulo_servo);
        mensagemEmFila = true;
    }
    // else if (alterna_motor())
    // {
    //     doc["MotorState"] = motorLigado;
    //     mensagemEmFila = true;
    // }
    if (mensagemEmFila)
    {
        serializeJson(doc, json);
        publica_mqtt(mqtt_topic1, json);
        mensagemEmFila = false;
    }
}
