#include <Arduino.h>
#include "motor.h"

const int MOTOR_PIN = 14; 
const int BUTTON_PIN = 0;  

#define CANALPWM 1
#define PWM_FREQ 1000  
#define PWM_RESOLUTION 8 

bool motorState = false;   

int currentDutyCycle = 0; 
int targetDutyCycle = 0;  
unsigned long previousMillis = 0; 
const long interval = 30;

void inicializa_motor_dc()
{
    pinMode(MOTOR_PIN, OUTPUT);
    ledcSetup(CANALPWM, PWM_FREQ, PWM_RESOLUTION);
    ledcAttachPin(MOTOR_PIN, CANALPWM);
    motorOff();
}

void atualiza_motor_dc()
{
  Motorloop();
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval)
  {
    previousMillis = currentMillis;

    if (currentDutyCycle != targetDutyCycle)
    {
      if (currentDutyCycle < targetDutyCycle)
      {
        currentDutyCycle += 5; 
        if (currentDutyCycle > targetDutyCycle) currentDutyCycle = targetDutyCycle;  
      }
      else if (currentDutyCycle > targetDutyCycle)
      {
        currentDutyCycle -= 5; 
        if (currentDutyCycle < targetDutyCycle) currentDutyCycle = targetDutyCycle;  
      }
      ledcWrite(CANALPWM, currentDutyCycle);
    }
  }
}


// void Motorloop()
// {
//     // Leitura do estado atual do botão
//     bool buttonState = digitalRead(BUTTON_PIN);

//     // Verifica transição de HIGH para LOW (botão pressionado)
//     if (buttonLastState == HIGH && buttonState == LOW)
//     {
//         // Alterna o estado do motor
//         if (motorState)
//         {
//             motorOff(); // Desliga o motor gradualmente
//             Serial.println("Motor desligado / Botao apertado");
//         }
//         else
//         {
//             motorOn(); // Liga o motor gradualmente
//             Serial.println("Motor Ligado / Botao apertado");
//         }

//         // Alterna o estado da variável motorState
//         motorState = !motorState;
//     }

//     // Atualiza o estado anterior do botão
//     buttonLastState = buttonState;
// }

void motorOn()
{
    targetDutyCycle = 130;  
    Serial.println("Motor ligado");
}

void motorOff()
{
    targetDutyCycle = 0;  
    Serial.println("Motor desligado");
}
