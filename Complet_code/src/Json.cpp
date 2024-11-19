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
#include "token.h"

#define mqtt_topic1 "projeto_auto_factory"

int mudasenha = Intervalo_Normal;
int TempoExtraSenha = Tempo_extra;
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
        //mensagem();
        time_anterior = millis();
        doc["timeStamp"] = timeStamp();
        doc["MudaSenha"] = mudasenha;
        doc["TempoExtra"] = TempoExtraSenha;
        doc["UIDCadastrado"] = numericUID;
        doc["UIDarmazenadoposicao"] = i_posicao;
        doc["UIDDetectado"] = pos;
        doc["MemoriaCheia"] = mc;
        doc["Temperatura"] = temperatura;
        doc["Umidade"] = humidade;
        doc["CO2"] = round(sensores_get_gas() * 100.0) / 100.0;
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
    else if (botao_passo_pressionado())
    {
        Serial.println("botao pressionado");
        buttonState = !buttonState;
        doc["EsteiraState"] = buttonState;
        mensagemEmFila = true;
    }
    else if (botao_passo_solto())
    {
        Serial.println("botao pressionado");
        buttonState = !buttonState;
        doc["EsteiraState"] = buttonState;
        mensagemEmFila = true;
    }
    if (mensagemEmFila)
    {
        serializeJson(doc, json);
        publica_mqtt(mqtt_topic1, json);
        Serial.println("Publicado Messagem: ");
        Serial.println(json);
        mensagemEmFila = false;
    }
}



