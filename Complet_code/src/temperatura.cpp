#include <Arduino.h>
#include <DHT.h>
#include <Adafruit_Sensor.h>
#include "temperatura.h"

#define DHTTYPE DHT22
#define DHTPIN 18

float temperatura;
float humidade;
unsigned long time_previous = 0;
const unsigned long intervalo = 1000;

DHT dht(DHTPIN, DHTTYPE);

void inicializa_temperatura()
{
    Serial.begin(9600);
    dht.begin();
}

void setup_temperatura()
{
    if (millis() - time_previous >= intervalo)
    {
        Serial.println("Temperatura:" + String(lerTemperatura()) + "ºC");
        Serial.println("Umidade:" + String(lerUmidade()) + "%");
        time_previous = millis();
    }
}

float lerTemperatura()
{
    temperatura = dht.readTemperature();
    return temperatura;
}

float lerUmidade()
{
    humidade = dht.readHumidity();
    return humidade;
}
