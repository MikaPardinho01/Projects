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

void setup()
{
    Serial.begin(9600);
    setup_wifi();
    setup_time();
    inicializa_saidas();
    inicializa_oled();
    inicializa_entradas();
    inicializa_servos();
    inicializa_temperatura();
    inicializa_oled();
    inicializa_nfc();
    sensores_init();
    inicializa_motor();
    Inicializa_senha();
    atualiza_nfc();
}

void loop()
{
    atualiza_mqtt();
    atualiza_saidas();
    atualiza_sinilizacao();
    inicializa_json();
    atualiza_botoes();
    lerTemperatura();
    lerUmidade();
}
