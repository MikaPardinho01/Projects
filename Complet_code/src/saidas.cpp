#include <Arduino.h>
#include "saidas.h"

#define Luz_central 2
#define vermelho_pin01 21
#define amarelo_pin01 22
#define vermelho_pin02 15
#define amarelo_pin02 2

bool LuzCentral = LOW;

void inicializa_saidas()
{
  pinMode(Luz_central, OUTPUT);
  pinMode(vermelho_pin01, OUTPUT);
  pinMode(amarelo_pin01, OUTPUT);
  pinMode(vermelho_pin02, OUTPUT);
  pinMode(amarelo_pin02, OUTPUT);
}

void atualiza_saidas()
{
  digitalWrite(Luz_central, LuzCentral);
}

void atualiza_sinilizacao()
{
  digitalWrite(vermelho_pin01, HIGH);
  digitalWrite(vermelho_pin02, HIGH);
  digitalWrite(amarelo_pin01, LOW);
  pinMode(amarelo_pin02, LOW);
  //delay(2000);
  digitalWrite(vermelho_pin01, LOW);
  digitalWrite(vermelho_pin02, LOW);
  digitalWrite(amarelo_pin01, HIGH);
  pinMode(amarelo_pin02, HIGH);
  //delay(2000);
}