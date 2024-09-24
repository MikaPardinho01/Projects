#include <Arduino.h>
#include <Bounce2.h>
#include "entradas.h"
#include "saidas.h"

// Definição dos pinos dos botões
#define BOTAO_EXTERNO_PIN 5
#define BOTAO_SERVO 22

// Criação dos objetos para debouncing

Bounce botaoExterno = Bounce();
Bounce botaoservo = Bounce();

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

// Retorna se o botão externo foi pressionado
bool botao_externo_pressionado()
{
    return botaoExterno.fell();
}

bool botao_externo_solto()
{
    return botaoExterno.rose();
}

// Retorna se o Botao do sero foi pressionado
bool botao_servo_pressionado()
{
    return botaoservo.fell();
}

bool botao_servo_solto()
{
    return botaoservo.rose();
}