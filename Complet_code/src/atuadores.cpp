#include <ESP32Servo.h>
#include "atuadores.h"

const int SERVO_PIN_ESTOQUE = 13;
const int SERVO_PIN_DESPACHE = 19;
int angulo_despache = 0;
int angulo_estoque = 0;

Servo servo_despache;
Servo servo_estoque; 

void inicializa_servos()
{
    try {
        servo_despache.attach(SERVO_PIN_DESPACHE, 500, 2500);
        servo_estoque.attach(SERVO_PIN_ESTOQUE, 500, 2500);
    } catch (const char* msg) {
         Serial.print(msg);
    }  
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