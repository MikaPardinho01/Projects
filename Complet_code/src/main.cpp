#include <Arduino.h>
#include <ArduinoJson.h>
#include "iot.h"
#include "tempo.h"



void setup()
{
    Serial.begin(115200);
    setup_wifi();
    setup_time();
    inicializa_mqtt();
}

void loop()
{
    atualiza_mqtt();
}