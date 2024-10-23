#include <Arduino.h>
#include "token.h"
#include "tempo.h"

int randNumber;

unsigned long NovoTempoExtra = 0;
unsigned long Intervalo_Troca = 0;
unsigned long Intervalo_Normal = 10000;
unsigned long Tempo_extra = 30000;
unsigned long tempo_anterior_token = 0;
unsigned long troca_Token = 0;

void Inicializa_senha()
{
    randomSeed(timeStamp());
}

int gera_senha()
{
    Reset_user();
    unsigned long tempo_atual = millis();
    if (tempo_atual - tempo_anterior_token >= troca_Token)
    {
        if (tempo_anterior_token != Intervalo_Normal) troca_Token = Intervalo_Normal;
        tempo_anterior_token = tempo_atual;
        randNumber = random(1000, 10000);
        Serial.print("\n");
        Serial.printf("Nova Senha: %d\n", randNumber);
    }
    return randNumber;
}

void tempo_extra()
{
    if (troca_Token != Tempo_extra)
    {
        tempo_anterior_token = millis();
        troca_Token = Tempo_extra;
        Serial.print("\n");
        Serial.printf("Senha estendida por %d segundos", Tempo_extra / 1000);
        Serial.print("\n");
    }
}