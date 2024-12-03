#include <Arduino.h>
#include <Bounce2.h>
#include "entradas.h"
#include "saidas.h"

const int BOTAO_LED = 0;
const int BOTAO_SERVO = 23;
const int BOTAO_MOTOR = 22;

Bounce botaoLed = Bounce();
Bounce botaoMotor = Bounce();
Bounce botaoservo = Bounce();

bool ledPowerState = false;
bool motorPowerState = false;
bool actionState = false;

void inicializa_entradas()
{
    botaoLed.attach(BOTAO_LED, INPUT_PULLUP);
    botaoMotor.attach(BOTAO_MOTOR, INPUT_PULLUP);
    botaoservo.attach(BOTAO_SERVO, INPUT_PULLUP);
}

void atualiza_botoes()
{
    botaoLed.update();
    botaoMotor.update();
    botaoservo.update();
}

bool botao_servo_pressionado()
{
    if (botaoservo.fell())
    {
        actionState = !actionState;
    }
    return botaoservo.fell();
}

bool botao_motor_pressionado()
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
