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

unsigned long time_anterior = 0;
unsigned long time_definido = 1000;
const int resposta = 0;

void inicializa_json()
{
    JsonDocument doc;
    String json;
    bool mensagemEmFila = false;

    if (millis() - time_anterior >= time_definido) {
        mensagem();
        time_anterior = millis();
        doc["timeStamp"] = timeStamp();
        doc["UIDCadastrado"] = numericUID;
        doc["UIDarmazenadoposicao"] = i_posicao;
        doc["UIDDetectado"] = pos;
        doc["MemoriaCheia"] = mc;
        doc["Temperatura"] = temperatura;
        doc["Umidade"] = humidade;
        doc["CO2"] = round(sensores_get_gas() * 100.0) / 100.0;
        mensagemEmFila = true;

    }  else if (botao_servo_estoque_pressionado()) {
        inicializa_servos();
        doc["PortaoEstoque"] = angulo_estoque;
        doc["BotaoservoState"] = servoPowerState;
        if (servoPowerState)
        
        {
            angulo_estoque = 90;
        }
        else
        {
            angulo_estoque = 0;
        }
        posiciona_servo_estoque(angulo_estoque);
        Serial.println(angulo_estoque);
        mensagemEmFila = true;

    } else if (botao_servo_despache_pressionado()) {
        inicializa_servos();
        doc["PortaoDespache"]  = angulo_despache;
        doc["PortaoState"] = actionState;
        if(actionState)
        {
            angulo_despache = 90;
        } 
        else 
        {
            angulo_despache = 0;
        }
        posiciona_servo_despache(angulo_despache);
        mensagemEmFila = true;
        
    } // else if (botao_motor_pressionado())
    // {
    //     doc["motorState"] = angulo_motor;
    //     doc["BotaomotorState"] = motorPowerState;
    //     if (motorPowerState > 3)
    //     {
    //         switch (motorPowerState)
    //         {
    //         case 0:
    //             analogWrite(motorPin, 0);
    //             break;
    //         case 1:
    //             analogWrite(motorPin, 85);
    //             break;
    //         case 2:
    //             analogWrite(motorPin, 100);
    //             break;
    //         case 3:
    //             analogWrite(motorPin, 150);
    //             break;
    //         }
    //     }
    //     atualiza_motor(angulo_motor);
    //     mensagemEmFila = true;
    // }
    else if (botao_led_pressionado()) {
        doc["LedState"] = ledPowerState;
        doc["BotaoledState"] = ledPowerState;
        if (ledPowerState)
        {
            atualiza_leds_branco();
        }
        else
        {
            atualiza_leds_apagado();
        }
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