#include <ESP32Servo.h>
#include "atuadores.h"

#define SERVO_PIN 2
int angulo_servo = 0;

Servo servoMotor; 

void inicializa_servos()
{
    servoMotor.attach(SERVO_PIN, 500, 2500);
}

void posiciona_servo(int posicao)
{
    angulo_servo = posicao;
    servoMotor.write(angulo_servo);
}