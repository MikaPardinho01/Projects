// *===== BIBLIOTECAS ======
#include <Arduino.h>
#include <Stepper.h> // incluir motor de passo
#include "entradas.h"
const int stepsPerRevolution = 2048; // número de passos para uma volta completa de 360 graus

// *===== DEFINICOES ======
#define IN1 19
#define IN2 18
#define IN3 5
#define IN4 17

// *===== OBJETOS ========
Stepper myStepper(stepsPerRevolution, IN1, IN3, IN2, IN4);

unsigned long previousMillis = 0; 
const long interval = 1000; 
bool motorLigado = false; 

void inicializa_motor() {
  myStepper.setSpeed(5);
}
void atualiza_motor() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    if (motorLigado) {
      Serial.println("Motor ligado - sentido horário");
      myStepper.step(stepsPerRevolution);
    } else {
      Serial.println("Motor desligado");
    }
  }
}
void alterna_motor() {
  motorLigado = !motorLigado; 
  if (motorLigado) {
    Serial.println("Motor ligado");
  } else {
    Serial.println("Motor desligado");
  }
}


