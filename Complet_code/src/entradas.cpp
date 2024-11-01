#include <Arduino.h>
#include <Bounce2.h>
#include "entradas.h"
#include "saidas.h"

const int BOTAO_EXTERNO_PIN = 14;
const int BOTAO_SERVO = 4;
const int BOTAO_PASSO = 0;

Bounce botaoExternoluz = Bounce();
Bounce botaoservo = Bounce();
Bounce botaoPasso = Bounce();

bool actionState = false;
bool buttonState = false;

void inicializa_entradas()
{
    botaoExternoluz.attach(BOTAO_EXTERNO_PIN, INPUT_PULLUP);
    botaoservo.attach(BOTAO_SERVO, INPUT_PULLUP);
    botaoPasso.attach(BOTAO_PASSO, INPUT_PULLUP);
}

void atualiza_botoes()
{
    botaoExternoluz.update();
    botaoservo.update();
    botaoPasso.update();
}

bool botao_externo_pressionado()
{
    return botaoExternoluz.fell();
}

bool botao_externo_solto()
{
    return botaoExternoluz.rose();
}

bool botao_servo_pressionado()
{
    if (botaoservo.fell())
    {
        actionState = !actionState;
        // Serial.println(actionState ? "Servo ligado" : "Servo desligado");
    }
    return botaoservo.fell();
}

bool botao_passo_pressionado()
{
    Serial.println("botao");
    return botaoPasso.fell();
}

bool botao_passo_solto()
{
    Serial.println("bb");
    return botaoPasso.rose();
}