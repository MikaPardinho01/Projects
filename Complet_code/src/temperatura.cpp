#include <Arduino.h>
#include <U8g2lib.h>
#include <DHT.h>
#include <Adafruit_Sensor.h>
#include "temperatura.h"

#define DHTTYPE DHT22
#define DHTPIN 18

float temperatura;
float humidade;
unsigned long time_previous = 0;
const unsigned long intervalo = 1000;

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);
DHT dht(DHTPIN, DHTTYPE);

void inicializa_temperatura()
{
    u8g2.begin();
    Serial.begin(9600);
    dht.begin();
}

void setup_temperatura()
{
    if (millis() - time_previous >= intervalo)
    {
        Serial.println("Temperatura:" + String(lerTemperatura()) + "ºC");
        Serial.println("Umidade:" + String(lerUmidade()) + "%");
        u8g2.clearBuffer();
        telaFundo();
        u8g2.sendBuffer();
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

void telaFundo()
{
    u8g2.drawRFrame(3, 3, 122, 27, 5);
    u8g2.drawRFrame(3, 34, 122, 27, 5);
    u8g2.setFont(u8g2_font_unifont_t_weather);
    u8g2.drawGlyph(5, 23, 0x31);
    u8g2.drawGlyph(5, 53, 0x32);
    u8g2.setFont(u8g2_font_lubBI12_te);
    u8g2.drawStr(30, 23, String(lerTemperatura(), 1).c_str());
    u8g2.drawStr(70, 23, "*C");
    u8g2.drawStr(30, 53, String(lerUmidade(), 0).c_str());
    u8g2.drawStr(60, 53, "%");
}