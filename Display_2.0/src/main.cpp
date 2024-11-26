#include <Arduino.h>

#include <LiquidCrystal_I2C.h>

#include <Bounce2.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

Bounce Botaoboot = Bounce();

byte caracter1[] = {

    B10001,

    B11011,

    B10101,

    B10001,

    B10001,

    B10001,

    B10001,

    B10001

};

void setup()
{

  Botaoboot.attach(0, INPUT_PULLUP);

  lcd.init();

  lcd.backlight();

  lcd.print("Botao solto");
}

void loop()
{
  Botaoboot.update();

  if (Botaoboot.fell())

  {

    lcd.setCursor(6, 0);

    lcd.print("pressionado");
  }

  else if (Botaoboot.rose())

  {

    lcd.setCursor(6, 0);

    lcd.print("solto       ");
  }
}