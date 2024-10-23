// *===== BIBLIOTECAS ======
#include <Arduino.h>
#include <Stepper.h> // incluir motor de passo

const int stepsPerRevolution = 2048; // é o número de passos que um motor de passo deve dar para completar uma volta completa de 360 graus.

// *===== DEFINICOES ======
// Pins setados no motor de passo
#define IN1 19
#define IN2 18
#define IN3 5
#define IN4 17

// *===== OBJETOS ========
// inicializar a biblioteca do motor (stepper)
Stepper myStepper(stepsPerRevolution, IN1, IN3, IN2, IN4);

unsigned long previousMillis = 0; // variável para armazenar o tempo anterior
const long interval = 1000; // intervalo de tempo em milissegundos (1 segundo)

bool motorLigado = false; // variável para rastrear o estado do motor

void inicializa_motor() 
{
  // define a velocidade em 5 rpm (é uma medida de quantas voltas completas um objeto ou motor faz em um minuto.)
  myStepper.setSpeed(5);
  Serial.begin(115200);
  Serial.println("Motor desligado");
}

void atualiza_motor() 
{
  unsigned long currentMillis = millis(); // obtém o tempo atual em milissegundos

  if (currentMillis - previousMillis >= interval) 
  {
    // salva o tempo atual
    previousMillis = currentMillis;

    if (motorLigado) 
    {
      // passo uma revolução em uma direção:
      Serial.println("Motor ligado - sentido horário");
      myStepper.step(stepsPerRevolution);
    }
    else 
    {
      Serial.println("Motor desligado");
    }
  }
}

void alterna_motor()
{
  motorLigado = !motorLigado; // alterna entre ligado e desligado
  if (motorLigado) {
    Serial.println("Motor ligado");
  } else {
    Serial.println("Motor desligado");
  }
}

void setup() {
  inicializa_motor();
}

void loop() {
  atualiza_motor();
  // Simulando alternância de estado do motor a cada 5 segundos (5000 ms)
  if (millis() % 5000 < 1000) { 
    alterna_motor();
  }
}
