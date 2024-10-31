#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Display.h>

LiquidCrystal_I2C lcd(0x27, 28, 4);

byte vintePorCento[] = {
    B10000,
    B10000,
    B10000,
    B10000,
    B10000,
    B10000,
    B10000,
    B10000};

byte quarentaPorCento[] = {
    B11000,
    B11000,
    B11000,
    B11000,
    B11000,
    B11000,
    B11000,
    B11000};

byte sessentaPorCento[] = {
    B11100,
    B11100,
    B11100,
    B11100,
    B11100,
    B11100,
    B11100,
    B11100};

byte oitentaPorCento[] = {
    B11110,
    B11110,
    B11110,
    B11110,
    B11110,
    B11110,
    B11110,
    B11110};

void inicializaLCD()
{
    lcd.init();
    lcd.backlight();
    lcd.createChar(0, vintePorCento);
    lcd.createChar(1, quarentaPorCento);
    lcd.createChar(2, sessentaPorCento);
    lcd.createChar(3, oitentaPorCento);
}

void temporizador(byte linha, int tempo, int tempoTotal)
{
    lcd.setCursor(0, linha);
    byte blocoPreenchidos = tempo * 20 / tempoTotal;
    byte blocoParcial = map ((tempo * 20) % tempoTotal, 0, tempoTotal, 0, 4);

    for (int i = 0; i < blocoPreenchidos; i++)
    {
        lcd.write(byte(255));
    }
    if (blocoParcial > 0)
    {
        lcd.write(byte(blocoParcial));
    }
    for (int i = 0; i < (20 - blocoPreenchidos); i++)
    {
        lcd.print(" ");
    }
}