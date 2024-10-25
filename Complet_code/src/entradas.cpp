#include <Arduino.h>
#include <Bounce2.h>
#include "entradas.h"
#include "saidas.h"

// Definição dos pinos dos botões
#define BOTAO_EXTERNO_PIN 14
#define BOTAO_SERVO 4
// #define BOTAO_CONTROLE 4

// Criação dos objetos para debouncing

Bounce botaoExternoluz = Bounce();
Bounce botaoservo = Bounce();
// Bounce botaoControle = Bounce();

bool actionState = false;
bool actionControll = false;

// Inicializa as entradas digitais
void inicializa_entradas()
{
    botaoExternoluz.attach(BOTAO_EXTERNO_PIN, INPUT_PULLUP);
    botaoservo.attach(BOTAO_SERVO, INPUT_PULLUP);
    // botaoControle.attach(BOTAO_CONTROLE, INPUT_PULLUP);
}

// Atualiza o estado dos botões
void atualiza_botoes()
{
    botaoExternoluz.update();
    botaoservo.update();
    // botaoControle.update();
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
        Serial.println(actionState ? "Servo ligado" : "Servo desligado");
    }
    return botaoservo.fell();
}

// bool botao_servo_solto()
// {
//     return botaoservo.rose();
// }

// bool botao_controle_solto()
// {
//     if (botaoControle.fell())
//     {
//         actionControll = !actionControll;
//     }
//     return botaoControle.fell();
// }

