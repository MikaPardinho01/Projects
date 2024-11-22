#include <Adafruit_NeoPixel.h>

// Configuração dos LEDs WS2811 para a funcionalidade 1
#define LED_PIN_1 4
#define NUM_LEDS_1 2
#define COLOR_CHANGE_INTERVAL 1000 // Intervalo de 1 segundo

Adafruit_NeoPixel strip1(NUM_LEDS_1, LED_PIN_1, NEO_GRB + NEO_KHZ800);
unsigned long previousMillis1 = 0;
bool toggle = false;

// Configuração dos LEDs WS2811 para a funcionalidade 2
#define LED_PIN_2 6
#define NUM_LEDS_2 10

Adafruit_NeoPixel strip2(NUM_LEDS_2, LED_PIN_2, NEO_GRB + NEO_KHZ800);

void setup() {
    // Inicializa os LEDs para a funcionalidade 1
    strip1.begin();
    strip1.show(); // Apaga todos os LEDs
    strip1.clear();

    // Inicializa os LEDs para a funcionalidade 2
    strip2.begin();
    strip2.show(); // Apaga todos os LEDs
    strip2.clear();

    // Configura a fita 2 (pino 6) para branco
    for (int i = 0; i < NUM_LEDS_2; i++) {
        strip2.setPixelColor(i, strip2.Color(255, 255, 255)); // Branco
    }
    strip2.show();
}

void loop() {
    // Controle da funcionalidade 1 (alternar entre vermelho e amarelo)
    unsigned long currentMillis1 = millis();
    if (currentMillis1 - previousMillis1 >= COLOR_CHANGE_INTERVAL) {
        previousMillis1 = currentMillis1;
        toggle = !toggle;

        // Alterna as cores
        if (toggle) {
            strip1.setPixelColor(0, strip1.Color(255, 0, 0)); // Vermelho
            strip1.setPixelColor(1, strip1.Color(255, 255, 0)); // Amarelo
        } else {
            strip1.setPixelColor(0, strip1.Color(255, 255, 0)); // Amarelo
            strip1.setPixelColor(1, strip1.Color(255, 0, 0)); // Vermelho
        }
        strip1.show();
    }

    // A fita 2 permanece estática em branco
}
