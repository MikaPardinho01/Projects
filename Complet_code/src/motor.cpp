#include <Arduino.h>
#include "motor.h"

#define MOTOR_PIN 14  
#define CANALPWM 1    
#define PWM_FREQ 1000 
#define PWM_RESOLUTION 8 

int currentDutyCycle = 0;  
int targetDutyCycle = 0;   
unsigned long previousMillis = 0; 
const long interval = 30;  

bool motorState = LOW; 

void inicializa_motor_dc()
{
    pinMode(MOTOR_PIN, OUTPUT);                
    ledcSetup(CANALPWM, PWM_FREQ, PWM_RESOLUTION); 
    ledcAttachPin(MOTOR_PIN, CANALPWM);        
    // ledcWrite(CANALPWM, 0);                    
}

void atualiza_motor_dc()
{
    unsigned long currentMillis = millis(); 
    if (currentMillis - previousMillis >= interval)
    {
        previousMillis = currentMillis;

        if (currentDutyCycle != targetDutyCycle)
        {
            if (currentDutyCycle < targetDutyCycle)
            {
                currentDutyCycle += 5; 
                if (currentDutyCycle > targetDutyCycle)
                    currentDutyCycle = targetDutyCycle;
            }
            else if (currentDutyCycle > targetDutyCycle)
            {
                currentDutyCycle -= 5;
                if (currentDutyCycle < targetDutyCycle)
                    currentDutyCycle = targetDutyCycle;
            }
            ledcWrite(CANALPWM, currentDutyCycle); 
        }
    }
}

void motorOn()
{
    targetDutyCycle = 100;  // Define o valor final do duty cycle para ligar o motor
    Serial.println("Motor ligado");
}

// Função para desligar o motor DC gradualmente
void motorOff()
{
    targetDutyCycle = 0;  // Define o valor final do duty cycle para desligar o motor
    Serial.println("Motor desligado");
}
