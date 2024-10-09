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

void setup()
{
    Serial.begin(9600);
    setup_wifi();
    setup_time();
    inicializa_saidas();
    // atualiza_totem();
    inicializa_entradas();
    inicializa_servos();
    // inicializa_temperatura();
    inicializa_u8g2();
    inicializa_nfc();
}

void loop()
{
    atualiza_mqtt();
    atualiza_saidas();
    atualiza_sinilizacao();
    inicializa_json();
    atualiza_botoes(); 
    // inicializa_totem();
    // setup_temperatura();
    atualiza_nfc();
}
