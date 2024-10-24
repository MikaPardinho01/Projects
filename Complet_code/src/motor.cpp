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

/*************  ✨ Codeium Command ⭐  *************/
/**
 * Atualiza o estado do motor de passo.
 * 
 * Esta função verifica se o intervalo de tempo especificado já passou
 * desde a última atualização. Se o tempo tiver passado, ela alterna
/******  cbce47f7-2aa5-4832-9fff-811b7837b2d3  *******/
bool atualiza_motor() 
{
  unsigned long currentMillis = millis(); // obtém o tempo atual em milissegundos

  if (currentMillis - previousMillis >= interval) 
  {
    // salva o tempo atual
    previousMillis = currentMillis;

    if (motorLigado) 
    {
      // passo uma revolução em uma direção:
      return motorLigado = printf("Motor ligado - sentido horário");
      myStepper.step(stepsPerRevolution);
    } 
    else 
    {
      return motorLigado = printf("Motor desligado");
    }
  }
}

bool alterna_motor()
{
  motorLigado = !motorLigado; // alterna entre ligado e desligado
  if (motorLigado) {
    return motorLigado = printf("Motor ligado");
  } else {
    return motorLigado = printf("Motor desligado");
  }
}
