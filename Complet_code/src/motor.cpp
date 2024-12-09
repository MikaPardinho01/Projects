#include <Arduino.h>

#define MOTOR_PIN 14  // Pino onde o motor está conectado
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

int currentDutyCycle = 0;  // Valor atual do duty cycle
int targetDutyCycle = 0;   // Valor final do duty cycle (0 para desligado, 255 para ligado)
unsigned long previousMillis = 0;  // Armazena o último tempo em que o duty cycle foi atualizado
const long interval = 30;  // Intervalo de tempo entre mudanças de duty cycle (em milissegundos)

void setup()
{
  Serial.begin(115200);
  MotorSetup();
}

void loop()
{
  Motorloop();

  // Verifica se é hora de atualizar o duty cycle (com base no tempo decorrido)
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval)
  {
    previousMillis = currentMillis;

    // Se o motor está ligando ou desligando, ajusta o duty cycle gradualmente
    if (currentDutyCycle != targetDutyCycle)
    {
      if (currentDutyCycle < targetDutyCycle)
      {
        currentDutyCycle += 5; // Aumenta gradualmente o duty cycle
        if (currentDutyCycle > targetDutyCycle) currentDutyCycle = targetDutyCycle;  // Garante que não ultrapasse o valor alvo
      }
      else if (currentDutyCycle > targetDutyCycle)
      {
        currentDutyCycle -= 5; // Diminui gradualmente o duty cycle
        if (currentDutyCycle < targetDutyCycle) currentDutyCycle = targetDutyCycle;  // Garante que não vá abaixo do valor alvo
      }
      ledcWrite(CANALPWM, currentDutyCycle);
    }
  }
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
            motorOff(); // Desliga o motor gradualmente
            Serial.println("Motor desligado / Botao apertado");
        }
        else
        {
            motorOn(); // Liga o motor gradualmente
            Serial.println("Motor Ligado / Botao apertado");
        }

        // Alterna o estado da variável motorState
        motorState = !motorState;
    }

    // Atualiza o estado anterior do botão
    buttonLastState = buttonState;
}

// Função para ligar o motor DC gradualmente
void motorOn()
{
    targetDutyCycle = 130;  // Define o valor final do duty cycle para ligar o motor
    Serial.println("Motor ligado");
}

// Função para desligar o motor DC gradualmente
void motorOff()
{
    targetDutyCycle = 0;  // Define o valor final do duty cycle para desligar o motor
    Serial.println("Motor desligado");
}
