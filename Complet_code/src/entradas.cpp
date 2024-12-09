#include <Arduino.h>
#include <Bounce2.h>
#include "entradas.h"
#include "saidas.h"

const int BOTAO_LED = 2;
const int BOTAO_SERVO_DESPACHE = 5;
const int BOTAO_SERVO_ESTOQUE = 23;
const int BOTAO_MOTOR = 0;

Bounce botaoservoDespache = Bounce();
Bounce botaoServoEstoque = Bounce();
Bounce botaoLed = Bounce();
Bounce botaoMotor = Bounce();

bool servoPowerState = false;
bool ledPowerState = false;
bool motorPowerState = false;
bool actionState = false;

void inicializa_entradas()
{
    botaoServoEstoque.attach(BOTAO_SERVO_ESTOQUE, INPUT_PULLUP);
    botaoLed.attach(BOTAO_LED, INPUT_PULLUP);
    botaoMotor.attach(BOTAO_MOTOR, INPUT_PULLUP);
    botaoservoDespache.attach(BOTAO_SERVO_DESPACHE, INPUT_PULLUP);
}

void atualiza_botoes()
{
    botaoServoEstoque.update();
    botaoLed.update();
    botaoMotor.update();
    botaoservoDespache.update();
}

bool botao_servo_despache_pressionado()
{
    if (botaoservoDespache.fell())
    {
        actionState = !actionState;
    }
    return botaoservoDespache.fell();
}

bool botao_servo_estoque_pressionado()
{
    if (botaoServoEstoque.fell())
    {
        servoPowerState = !servoPowerState;
    }
    return botaoServoEstoque.fell();
}

bool botao_motor_dc_pressionado()
{
    if (botaoMotor.fell())
    {
        motorPowerState = !motorPowerState;
    }
    return botaoMotor.fell();
}

bool botao_led_pressionado()
{
    if (botaoLed.fell())
    {
        ledPowerState = !ledPowerState;
    }
    return botaoLed.fell();
}


