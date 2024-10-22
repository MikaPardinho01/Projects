#include <Arduino.h>
#include <Bounce2.h>
#include "entradas.h"
#include "saidas.h"

// Definição dos pinos dos botões
#define BOTAO_EXTERNO_PIN 4
#define BOTAO_SERVO 14
// #define BOTAO_CONTROLE 4
#define BOTAO_NFC 0

// Criação dos objetos para debouncing

Bounce botaoExternoluz = Bounce();
Bounce botaoservo = Bounce();
// Bounce botaoControle = Bounce();
Bounce botaoNfc = Bounce();

bool actionState = false;
bool actionControll = false;
bool actionNFC = false;

// Inicializa as entradas digitais
void inicializa_entradas()
{
    botaoExternoluz.attach(BOTAO_EXTERNO_PIN, INPUT_PULLUP);
    botaoservo.attach(BOTAO_SERVO, INPUT_PULLUP);
    // botaoControle.attach(BOTAO_CONTROLE, INPUT_PULLUP);
    botaoNfc.attach(BOTAO_NFC, INPUT_PULLUP);
}

// Atualiza o estado dos botões
void atualiza_botoes()
{
    botaoExternoluz.update();
    botaoservo.update();
    // botaoControle.update();
    botaoNfc.update();
}

bool botao_externo_pressionado()
{
    return botaoExternoluz.fell();
}

bool botao_externo_solto()
{
    return botaoExternoluz.rose();
}

bool botao_nfc_pressionado()
{
    return botaoNfc.fell();
}

bool botao_nfc_solto()
{
    return botaoNfc.rose();
}

bool botao_servo_pressionado()
{
    if (botaoservo.fell())
    {
        actionState = !actionState;
    }
    return botaoservo.fell();
}
bool botao_pressionado_nfc()
{
    if (botaoNfc.fell())
    {
        actionNFC = !actionNFC;
    }
    return botaoNfc.fell();
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

