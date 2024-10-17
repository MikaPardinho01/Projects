#include <Adafruit_BMP280.h>
#include <MQUnifiedsensor.h>

#define MQ_135_PIN 34
#define ADC_RESOLUTION_BIT 12

Adafruit_BMP280 bmp;
MQUnifiedsensor MQ135("ESP-32", 3.3, ADC_RESOLUTION_BIT, MQ_135_PIN, "MQ-135");

void sensores_init()
{
    if (!bmp.begin(0x76))
    {
        Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
    }

    MQ135.setRegressionMethod(1);

    MQ135.setA(36974);
    MQ135.setB(-3.109);

    MQ135.init();

    Serial.print("Calibrando, por favor aguarde.");
    float calcR0 = 0;

    for (int i = 1; i <= 10; i++)
    {
        MQ135.update();
        calcR0 += MQ135.calibrate(4.4);
        Serial.print(".");
    }

    calcR0 /= 10;
    MQ135.setR0(calcR0);
    Serial.println("  Concluído!");

    if (isinf(calcR0))
    {
        Serial.println("Aviso: Problema de conexão, R0 é infinito (Circuito aberto detectado). Verifique o cabeamento e a alimentação.");
    }
    else if (calcR0 == 0)
    {
        Serial.println("Aviso: Problema de conexão detectado, R0 é zero (Pino analógico em curto-circuito com o terra). Verifique o cabeamento e a alimentação.");
    }
    else
    {
        Serial.print("R0 calibrado para: ");
        Serial.println(calcR0);
    }
}

float sensores_get_gas()
{
    MQ135.update();
    return MQ135.readSensor();
}