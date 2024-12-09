#include <Arduino.h>
#include <ArduinoJson.h>
#include "iot.h"
#include "tempo.h"
#include "saidas.h"
#include "json.h"
#include "entradas.h"
#include "atuadores.h"
#include "temperatura.h"
#include "display.h"
#include "nfc_rfid.h"
#include "sensor.Gas.h"
#include "motor.h"
#include "token.h"

#define debug 1

void setup()
{
    if (debug) {
        Serial.begin(115200);
        Serial.println("inicializando a Serial");
        setup_wifi();
        Serial.println("Inicializando o WIFI");
        setup_time();
        Serial.println("Iniciaizando função de tempo");
        inicializa_token();
        Serial.println("incializando a senha");
        inicializa_entradas();
        Serial.println("Inicializando as entradas");
        //inicializa_servos();
        // Serial.println("Inicializando os servos");
        inicializa_temperatura();
        Serial.println("icializando a temperatura");
        inicializa_nfc();
        Serial.println("Inicializando o NFC");
        sensores_init();
        Serial.println("Inicializando os sensores");
        inicializa_motor_dc();
        Serial.println("incializando o motor dc");
        inicializa_oled();
        Serial.println("incializando o display");
        inicializa_leds();
        Serial.println("incializando os leds");
    }
}

void loop()
{
    atualiza_mqtt();
    atualiza_token();
    atualiza_botoes();
    setup_temperatura();
    atualiza_nfc();
    inicializa_json();
    alterna_cores();
    atualiza_oled();
}
