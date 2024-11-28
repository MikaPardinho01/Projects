#include <Arduino.h>
#include <Bounce2.h>
#include "entradas.h"
#include "saidas.h"

const int BOTAO_SERVO = 23;
const int BOTAO_PASSO = 0;
const int BOTAO_MOTOR = 2;

Bounce botaoMotor = Bounce();
Bounce botaoservo = Bounce();
Bounce botaoPasso = Bounce();

bool motorPowerState = false;
bool actionState = false;
bool buttonState = false;

void inicializa_entradas()
{
    botaoMotor.attach(BOTAO_MOTOR, INPUT_PULLUP);
    botaoservo.attach(BOTAO_SERVO, INPUT_PULLUP);
    botaoPasso.attach(BOTAO_PASSO, INPUT_PULLUP);
}

void atualiza_botoes()
{
    botaoMotor.update();
    botaoservo.update();
    botaoPasso.update();
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

bool botao_passo_pressionado()
{
    return botaoPasso.fell();
}

bool botao_passo_solto()
{
    return botaoPasso.rose();
}