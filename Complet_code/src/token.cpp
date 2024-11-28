#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include "token.h"

LiquidCrystal_I2C lcd(0x27, 20, 4); 

const unsigned long intervaloTroca = 90000; 
unsigned long tempoAnterior = 0;

int senhaAtual;

void inicializa_token() 
{
    lcd.init();
    lcd.backlight();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Gerador de Senha");
    randomSeed(analogRead(0));

    senhaAtual = gerarSenha();
    mostrarSenha(senhaAtual);
}

void atualiza_token() 
{
    unsigned long tempoAtual = millis();

    if (tempoAtual - tempoAnterior >= intervaloTroca) {
        tempoAnterior = tempoAtual;
        senhaAtual = gerarSenha();
        mostrarSenha(senhaAtual);
    }

    mostrarTempoRestante(intervaloTroca - (millis() - tempoAnterior));
}

int gerarSenha() 
{
    int senha = random(1000, 10000); 
    Serial.print("Nova senha gerada: ");
    Serial.println(senha);
    return senha;
}

void mostrarSenha(int senha) 
{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Senha Atual:");
    lcd.setCursor(0, 1);
    lcd.print(senha);
}

void mostrarTempoRestante(unsigned long tempoRestante)
{
    lcd.setCursor(0, 2);
    lcd.print("Troca em: ");
    lcd.print(tempoRestante / 1000);
    lcd.print("s ");
}
