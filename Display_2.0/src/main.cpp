#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Bounce2.h>

#define PIN_BOTAO 0

Bounce botao = Bounce();
LiquidCrystal_I2C lcd(0x27, 28, 4);

bool acctive = false;

void setup()
{
  lcd.init(); // Inicializa o LCD
  lcd.backlight(); // inicializa a luz de fundo
  lcd.setCursor(0, 0); // posiciona o cursor na coluna 0 e linha 0
  lcd.print("Hello, World!"); // Escreve 

  // Primeiro posiciona o cursor, depois o texto
  lcd.setCursor(0, 1); 
  lcd.print("Mika");
  lcd.setCursor(0, 2); 
  lcd.print("Senai");
  lcd.setCursor(0, 3); 
  lcd.print("2024");
  delay(3000);  // aguarda 3 segundos (trocar por millis)
  lcd.clear(); // limpa a tela

  botao.attach(PIN_BOTAO, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop()
{
  botao.update();
  if (botao.fell()) 
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Botao press");
  }
  else if (botao.rose())
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Botao nao press");
  }
}