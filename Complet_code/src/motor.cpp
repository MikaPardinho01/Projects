#include <Arduino.h>

const int motorPin = 9;

int motorPowerState = 0;

void inicializa_motor()
{
  pinMode(motorPin, OUTPUT);
}

void atualiza_motor(int posicao_motor)
{
  motorPowerState = posicao_motor;
  digitalWrite(motorPin, motorPowerState);
}
