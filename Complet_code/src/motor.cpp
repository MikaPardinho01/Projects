#include <Arduino.h>
#include <SPI.h>
#include <FS.h>
#include "SPIFFS.h"

#define MOTOR_PIN 5  // Pino onde o motor está conectado
#define BUTTON_PIN 0  // Pino onde o botão está conectado

void MotorSetup();
void Motorloop();
void motorOn();
void motorOff();

#define CANALPWM 1
#define PWM_FREQ 1000    // Frequência PWM
#define PWM_RESOLUTION 8 // Resolução do PWM (8 bits)

bool motorState = false;      // Estado atual do motor (false = desligado, true = ligado)
bool buttonLastState = LOW;  // Armazena o estado anterior do botão

void setup()
{
  Serial.begin(115200);
  MotorSetup();
}

void loop()
{
  Motorloop();
}

void MotorSetup()
{
    // Configura o pino do motor como saída
    pinMode(MOTOR_PIN, OUTPUT);

    // Configura o pino do botão como entrada com pull-up
    pinMode(BUTTON_PIN, INPUT_PULLUP);

    // Configura o canal PWM
    ledcSetup(CANALPWM, PWM_FREQ, PWM_RESOLUTION);

    // Associa o pino do motor ao canal PWM
    ledcAttachPin(MOTOR_PIN, CANALPWM);

    // Inicializa o motor desligado
    motorOff();
}

void Motorloop()
{
    // Leitura do estado atual do botão
    bool buttonState = digitalRead(BUTTON_PIN);

    // Verifica transição de HIGH para LOW (botão pressionado)
    if (buttonLastState == HIGH && buttonState == LOW)
    {
        // Alterna o estado do motor
        if (motorState)
        {
            motorOff(); // Desliga o motor
            Serial.println("Motor desligado / Botao apertado");
        }
        else
        {
            motorOn(); // Liga o motor
            Serial.println("Motor Ligado / Botao apertado");
        }

        // Alterna o estado da variável motorState
        motorState = !motorState;
    }

    // Atualiza o estado anterior do botão
    buttonLastState = buttonState;
}

// Função para ligar o motor DC
void motorOn()
{
    ledcWrite(CANALPWM, 150); // Liga o motor com 50% de duty cycle (PWM 128)
    Serial.println("Motor ligado");
}

// Função para desligar o motor DC
void motorOff()
{
    ledcWrite(CANALPWM, 0); // Desliga o motor (PWM 0)
    Serial.println("Motor desligado");
}