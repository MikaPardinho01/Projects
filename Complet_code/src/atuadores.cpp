#include <ESP32Servo.h>
#include "atuadores.h"

const int SERVO_PIN = 26;
const int servoPin = 33;

int angulo_despache = 0;
int angulo_estoque = 0;

Servo servo_despache;
Servo servo_estoque; 

void inicializa_servos()
{
    servo_despache.attach(SERVO_PIN, 500, 2500);
    servo_estoque.attach(servoPin, 500, 2500);
}

void posiciona_servo_despache(int posicao)
{
    angulo_despache = posicao;
    servo_despache.write(angulo_despache);
}

void posiciona_servo_estoque(int posicao_estoque)
{
    angulo_estoque = posicao_estoque;
    servo_estoque.write(angulo_estoque);
}