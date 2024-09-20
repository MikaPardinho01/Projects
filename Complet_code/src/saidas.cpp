#include <Arduino.h>
#include "saidas.h"

#define Luz_central 2
#define vermelho_pin01 21
#define amarelo_pin01 22
#define vermelho_pin02 15
#define amarelo_pin02 55

unsigned long time_anterior = 0;
unsigned long intervalo = 1000;

bool LuzCentral = LOW;
bool vermelhoPin01 = LOW;
bool vermelhoPin02 = LOW;
bool amareloPin01 = LOW;
bool amareloPin02 = LOW;

void inicializa_saidas()
{
  pinMode(Luz_central, OUTPUT);
  pinMode(vermelho_pin01, OUTPUT);
  pinMode(amarelo_pin01, OUTPUT);
  pinMode(vermelho_pin02, OUTPUT);
  // pinMode(amarelo_pin02, OUTPUT);
}

void atualiza_saidas()
{
  digitalWrite(Luz_central, LuzCentral);
  digitalWrite(vermelho_pin01, vermelhoPin01);
  digitalWrite(vermelho_pin02, vermelhoPin02);
  digitalWrite(amarelo_pin01, amareloPin01);
  digitalWrite(amarelo_pin02, amareloPin02);
}

void atualiza_sinilizacao()
{
  if (millis() - time_anterior >= intervalo)
  {
    vermelhoPin01 = !vermelhoPin01;
    vermelhoPin02 = !vermelhoPin02;
    amareloPin01 = !amareloPin01;
    amareloPin02 = !amareloPin02;
    time_anterior = millis();
  }
}