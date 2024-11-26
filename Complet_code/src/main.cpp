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
    Serial.begin(115200);
    if(debug) Serial.println("inicializando a Serial");
    setup_wifi();
    if(debug) Serial.println("Inicializando o WIFI");
    setup_time();
    if(debug) Serial.println("Iniciaizando função de tempo");
    inicializa_entradas();
    if(debug) Serial.println("Inicializando as entradas");
    inicializa_servos();
    if(debug) Serial.println("Inicializando os servos");
    inicializa_temperatura();
    if(debug) Serial.println("icializando a temperatura");
    inicializa_nfc();
    if(debug) Serial.println("Inicializando o NFC");
    sensores_init();
    if(debug) Serial.println("Inicializando os sensores");
    inicializa_motor();
    if(debug) Serial.println("incializando o motor");
    // inicializa_token();
   if(debug) Serial.println("incializando a senha");
    inicializa_display();
    if(debug) Serial.println("incializando o display");
}

void loop()
{
    atualiza_mqtt();
    atualiza_botoes();
    // atualiza_token();
    setup_temperatura();
    atualiza_motor();
    atualiza_nfc();
    inicializa_json();

}
