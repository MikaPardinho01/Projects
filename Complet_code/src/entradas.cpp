#include <Arduino.h>
#include <Bounce2.h>
#include "entradas.h"
#include "saidas.h"

const int BOTAO_SERVO = 23;
const int BOTAO_PASSO = 0;

Bounce botaoservo = Bounce();
Bounce botaoPasso = Bounce();

bool actionState = false;
bool buttonState = false;

void inicializa_entradas()
{
    botaoservo.attach(BOTAO_SERVO, INPUT_PULLUP);
    botaoPasso.attach(BOTAO_PASSO, INPUT_PULLUP);
}

void atualiza_botoes()
{
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

bool botao_passo_pressionado()
{
    return botaoPasso.fell();
}

bool botao_passo_solto()
{
    return botaoPasso.rose();
}