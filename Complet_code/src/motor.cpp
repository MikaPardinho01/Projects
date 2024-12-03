#include <Arduino.h>
#include "motor.h"

#define CANALPWM 0

const int motorPin = 21;
int angulo_motor = 0;

void inicializa_motor()
{
  ledcSetup(CANALPWM, 100, 8);
  ledcAttachPin(motorPin, CANALPWM);
  Serial.println("Motor inicializado");
}

void atualiza_motor(int posicao_motor)
{
  // angulo_motor = posicao_motor;
  ledcWrite(CANALPWM, 200);
  // analogWrite(motorPin, angulo_motor);
  // Serial.println("Motor atualizado");
}
