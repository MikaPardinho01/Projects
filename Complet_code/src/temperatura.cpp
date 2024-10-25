#include <Arduino.h>
#include <DHT.h>
#include <Adafruit_Sensor.h>
#include "temperatura.h"
#include "tempo.h"

#define DHTTYPE DHT22
#define DHTPIN 25

float temperatura;
float humidade;

unsigned long tempo_anterior = 1000;
unsigned long tempo_intervalo = 0;


DHT dht(DHTPIN, DHTTYPE);

void inicializa_temperatura()
{
    Serial.begin(9600);
    dht.begin();
}

// void setup_temperatura()
// {
//     if (millis() - tempo_anterior >= tempo_intervalo)
//     {
//         tempo_anterior = millis();
//         Serial.println("Temperatura:" + String(lerTemperatura()) + "ºC");
//         Serial.println("Umidade:" + String(lerUmidade()) + "%");    
//     }
// }

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
