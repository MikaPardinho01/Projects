#include <Arduino.h>
#include <ArduinoJson.h>
#include "iot.h"
#include "tempo.h"
#include "saidas.h"
#include "json.h"
#include "entradas.h"

void setup()
{
    Serial.begin(9600);
    setup_wifi();
    setup_time();
    inicializa_saidas();
}

void loop()
{
    atualiza_mqtt();
    atualiza_saidas();
    atualiza_sinilizacao();
    inicializa_json();
    atualiza_botoes();
}
