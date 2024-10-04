#include <Arduino.h>
#include "saidas.h"
#include "tempo.h"

// #define Luz_central 2
// #define vermelho_pin01 35
// #define amarelo_pin01 32
// #define vermelho_pin02 15
// #define amarelo_pin02 34

unsigned long timer_anterior = 1000;
unsigned long interval = 0;


bool LuzCentral = LOW;
bool vermelhoPin01 = LOW;
bool vermelhoPin02 = LOW;
bool amareloPin01 = LOW;
bool amareloPin02 = LOW;

void inicializa_saidas()
{
  // pinMode(Luz_central, OUTPUT);
  // pinMode(vermelho_pin01, OUTPUT);
  // pinMode(amarelo_pin01, OUTPUT);
  // pinMode(vermelho_pin02, OUTPUT);
  // pinMode(amarelo_pin02, OUTPUT);
}

void atualiza_saidas()
{
  // digitalWrite(Luz_central, LuzCentral);
  // digitalWrite(vermelho_pin01, vermelhoPin01);
  // digitalWrite(vermelho_pin02, vermelhoPin02);
  // digitalWrite(amarelo_pin01, amareloPin01);
  // digitalWrite(amarelo_pin02, amareloPin02);
}

void atualiza_sinilizacao()
{
  if (millis() - timer_anterior >= interval)
  {
    vermelhoPin01 = !vermelhoPin01;
    vermelhoPin02 = !vermelhoPin02;
    amareloPin01 = !amareloPin01;
    amareloPin02 = !amareloPin02;
    timer_anterior = millis();
  }
}