#include <Arduino.h>
#include <Bounce2.h>
#include "entradas.h"
#include "saidas.h"

// Definição dos pinos dos botões
#define BOTAO_EXTERNO_PIN 5
#define BOTAO_SERVO 27

// Criação dos objetos para debouncing

Bounce botaoExterno = Bounce();
Bounce botaoservo = Bounce();

bool actionState = false;

// Inicializa as entradas digitais
void inicializa_entradas()
{
    botaoExterno.attach(BOTAO_EXTERNO_PIN, INPUT_PULLUP);
    botaoservo.attach(BOTAO_SERVO, INPUT_PULLUP);
}

// Atualiza o estado dos botões
void atualiza_botoes()
{
    botaoExterno.update();
    botaoservo.update();
}

// Retorna se o botão externo foi pressionado ou nao
bool botao_externo_pressionado()
{
    return botaoExterno.fell();
}

bool botao_externo_solto()
{
    return botaoExterno.rose();
}

// Retorna se o Botao do sero foi pressionado ou nao
bool botao_servo_pressionado()
{
    if (botaoservo.fell())
    {
        actionState = !actionState;
    }
    return botaoservo.fell();
}

bool botao_servo_solto()
{
    return botaoservo.rose();
}