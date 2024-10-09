#include <Wire.h>
#include <Adafruit_PN532.h>
#include <Preferences.h>  

#define SDA_PIN 21
#define SCL_PIN 22

Adafruit_PN532 nfc(SDA_PIN, SCL_PIN);
Preferences preferences;  // Objeto para acessar a memória flash

const int maxUIDs = 10;  // Quantidade máxima de UIDs a serem armazenados

void setup(void) {
  Serial.begin(115200);
  Serial.println("Ola!");

  nfc.begin();

  uint32_t versiondata = nfc.getFirmwareVersion();
  if (!versiondata) {
    Serial.print("Não foi possível encontrar o PN53x");
    while (1);
  }

  nfc.SAMConfig();
  Serial.println("Esperando um cartão NFC...");

  // Inicia o NVS
  preferences.begin("UIDs", false);  // Namespace "UIDs", modo leitura/escrita
}

// Função para verificar se o UID já foi lido (é duplicado)
bool isDuplicateUID(unsigned long newUID) {
  for (int i = 0; i < maxUIDs; i++) {
    unsigned long storedUID = preferences.getULong(String(i).c_str(), 0);  // Recupera UID da posição i
    if (storedUID == newUID) {
      return true;  // UID já foi lido
    }
  }
  return false;  // UID não foi lido ainda
}

// Função para limpar a memória flash se o usuário der permissão
void clearMemoryIfAllowed() {
  Serial.println("Memória cheia! Deseja apagar todos os dados? (sim/não)");
  
  // Espera pela entrada do usuário
  while (!Serial.available()) {
    // Aguarda até que algo seja digitado no terminal
  }

  String resposta = Serial.readStringUntil('\n');  // Lê a resposta do usuário
  resposta.trim();  // Remove espaços extras
  
  if (resposta.equalsIgnoreCase("sim")) {
    Serial.println("Limpando a memória...");
    preferences.clear();  // Limpa todos os dados armazenados
    preferences.end();     // Fecha o armazenamento NVS
    preferences.begin("UIDs", false);  // Reinicia o armazenamento após limpeza
    Serial.println("Memória foi limpa.");
  } else {
    Serial.println("Memória mantida, nenhum dado foi excluído.");
  }
}

// Função para armazenar o UID no NVS (memória flash)
void storeUID(unsigned long newUID) {
  bool memoriaCheia = true;
  
  for (int i = 0; i < maxUIDs; i++) {
    unsigned long storedUID = preferences.getULong(String(i).c_str(), 0);
    if (storedUID == 0) {  // Encontra uma posição vazia
      preferences.putULong(String(i).c_str(), newUID);  // Armazena o novo UID
      Serial.print("UID armazenado na posição ");
      Serial.println(i);
      memoriaCheia = false;  // A memória não está cheia, pois encontramos uma posição
      break;
    }
  }
  
  if (memoriaCheia) {
    // Se chegarmos aqui, a memória está cheia
    clearMemoryIfAllowed();  // Pergunta ao usuário se deseja limpar a memória
  }
}

void loop(void) {
  uint8_t success;
  uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };  // Buffer para armazenar o UID
  uint8_t uidLength;

  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);

  if (success) {
    // Inicializa o número do UID como unsigned long
    unsigned long numericUID = 0;

    // Converte o UID em um número único
    for (byte i = 0; i < uidLength; i++) {
      numericUID = numericUID * 256 + uid[i];
    }

    // Exibe apenas o UID
    Serial.print("UID: ");
    Serial.println(numericUID);

    // Verifica se o UID é duplicado
    if (isDuplicateUID(numericUID)) {
      Serial.println("UID duplicado detectado!");
    } else {
      Serial.println("Novo UID detectado.");
      storeUID(numericUID);  // Armazena o novo UID na memória flash
    }

    delay(1000);
  }
}
