#include <Arduino.h>
#include "motor.h"

const int motorPin = 32;
int angulo_motor = 0;
#define CANALPWM 0

void inicializa_motor()
{
  ledcSetup(CANALPWM, 100, 8);
  ledcAttachPin(motorPin, CANALPWM);
}

void atualiza_motor(int posicao_motor)
{
  angulo_motor = posicao_motor;
  analogWrite(motorPin, angulo_motor);
}
