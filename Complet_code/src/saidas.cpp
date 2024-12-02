#include <FastLED.h>

// Configurações dos LEDs
#define LED_PIN     6    // Pino onde a fita de LED está conectada
#define NUM_LEDS    60   // Número de LEDs na fita
#define BUTTON_PIN  7    // Pino onde o botão está conectado
#define BRIGHTNESS  255  // Brilho máximo (0-255)

// Declaração dos LEDs
CRGB leds[NUM_LEDS];

// Variáveis de controle
bool ledsOn = false;       // Estado atual dos LEDs (ligado ou desligado)
bool lastButtonState = LOW; // Último estado do botão
unsigned long lastDebounceTime = 0; // Para evitar ruído no botão
unsigned long debounceDelay = 50;   // Tempo de debounce em milissegundos

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP); // Configura o botão como entrada com pull-up interno
  FastLED.addLeds<WS2811, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);

  // Inicializa todos os LEDs desligados
  FastLED.clear();
  FastLED.show();
}

void loop() {
  // Lê o estado atual do botão
  bool reading = digitalRead(BUTTON_PIN);

  // Verifica se houve uma mudança no botão
  if (reading != lastButtonState) {
    lastDebounceTime = millis(); // Reinicia o temporizador de debounce
  }

  // Se o tempo de debounce passou, atualiza o estado
  if ((millis() - lastDebounceTime) > debounceDelay) {
    // Verifica se o botão foi pressionado
    if (reading == LOW && lastButtonState == HIGH) {
      ledsOn = !ledsOn; // Alterna o estado dos LEDs
      updateLEDs();     // Atualiza os LEDs
    }
  }

  // Atualiza o último estado do botão
  lastButtonState = reading;
}

// Função para atualizar os LEDs
void updateLEDs() {
  if (ledsOn) {
    // Liga os LEDs com a cor branca
    fill_solid(leds, NUM_LEDS, CRGB::White);
  } else {
    // Desliga todos os LEDs
    FastLED.clear();
  }
  FastLED.show();
}
