// *===== BIBLIOTECAS ======
#include <Arduino.h>
#include <Stepper.h> // incluir motor de passo

const int stepsPerRevolution = 2048; // número de passos para uma volta completa de 360 graus

// *===== DEFINICOES ======
#define IN1 19
#define IN2 18
#define IN3 5
#define IN4 17
#define BUTTON_PIN 0

// *===== OBJETOS ========
Stepper myStepper(stepsPerRevolution, IN1, IN3, IN2, IN4);

unsigned long previousMillis = 0; // variável para armazenar o tempo anterior
const long interval = 1000; // intervalo de tempo em milissegundos (1 segundo)

bool motorLigado = false; // variável para rastrear o estado do motor
bool buttonState = false; // estado do botão
bool lastButtonState = false; // último estado do botão

void inicializa_motor() {
  // define a velocidade em 5 rpm
  myStepper.setSpeed(5);
  Serial.begin(115200);
  Serial.println("Motor desligado");

  pinMode(BUTTON_PIN, INPUT_PULLUP); // Configura o botão como entrada com resistor de pull-up interno
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

void verificaBotao() {
  buttonState = digitalRead(BUTTON_PIN); 

  if (buttonState != lastButtonState) {
    if (buttonState == LOW) {
      alterna_motor();
    }
    delay(50); 
  }
  lastButtonState = buttonState; 
}

void setup() {
  inicializa_motor();
}

void loop() {
  verificaBotao(); 
  atualiza_motor();
}
