#include <Arduino.h> // Inclui biblioteca principal Arduino
#include <Bounce2.h> // Inclui  biblioteca para controlar o botão
#include <Preferences.h> 

#define BotaoPin 0 // Pino do botão
#define TempoLimite 3000 // TempoLimite recebe 3000

Preferences preferences;
Bounce botao = Bounce();

int brilho; // Váriavel recebe inteiro para receber e armazenar brilho
int volume; // Váriavel recebe interio para receber e armazenar volume
unsigned long tempoPressionado = 0; // Tempo Pressionado

void ConfiguracaoPadrao() { // Confuguração inicial, tipo a do celular
  volume = 30; // Salva Volume, inicia em 30
  brilho = 30; // Salva Brilho, inicia em 30
  preferences.putInt("Volume", volume); preferences.putInt("Volume", volume); // Recupera o volume padrão (50)
  preferences.putInt("Brilho", brilho); // Recupera o brilho padrão (50)
  Serial.printf("Configuração Padrão, Brilho: %d, Volume: %d\n", brilho, volume); // Imprime os dois
}

void setup() {
  pinMode(BotaoPin, INPUT_PULLUP); // Configura o pino do botão com pullup
  Serial.begin(9600); // Inicia o Monitor Serial
  
  preferences.begin("config", false); // Inicia a Preferences com o namespace "config"

  brilho = preferences.getInt("Brilho", 30); // Recupera o valor salvo 
  volume = preferences.getInt("Volume", 30); // Recupera o valor salvo

  Serial.printf("Brilho: %d, Volume: %d\n", brilho, volume);

  botao.attach(BotaoPin); // Conecta o botao a bounce
  botao.interval(25);   
}

void loop() {
  botao.update(); // Atualiza o estado do botão

  static unsigned long TempoPrevisto = 0; // Váriavel estatica para contole de tempo
  unsigned long Tempo = millis(); // Pega o o tempo atual em millisegundos

  if (Tempo - TempoPrevisto >= 10000) { // A cada 10 segundos 
    TempoPrevisto = Tempo; // Atualiza o tempo previsto
    Serial.printf("Brilho: %d, Volume: %d\n", brilho, volume); // Imprime o brilho e volume
  }

  if (botao.read() == LOW) { // Se o botão for pressionado
    if (tempoPressionado == 0) { // Se não a tempo registrado
      tempoPressionado = millis(); // Marca o tempo em que o botão foi pressionado
    }
    
    // Se o botão foi pressionado por mais de 3 segundos (TempoLimite), reseta as configurações(No caso a configuração padrão)
    if (millis() - tempoPressionado > TempoLimite) {
      ConfiguracaoPadrao();
      tempoPressionado = 0; // Reseta o tempo
    }
  } else if (botao.read() == HIGH) {
    // Apenas incrementa volume e brilho se o botão não foi segurado por mais de 3 segundos
    if (tempoPressionado > 0 && millis() - tempoPressionado < TempoLimite) {
      volume = min(volume + 1, 100);        // Incrementa +1 quando o botão for pressionado; volume até 100
      brilho = min(brilho + 1, 100);        // Incrementa o brilho +1 quando o botão for pressionado; até 100
      preferences.putInt("Volume", volume); // Salva o novo valor de volume na flash
      preferences.putInt("Brilho", brilho); // Salva o novo valor de brilho na flash
      Serial.printf("Novo volume: %d\n", volume); 
      Serial.printf("Novo brilho: %d\n", brilho);
      delay(500); 
    }
    tempoPressionado = 0; // Reseta o contador de tempo
  }
}