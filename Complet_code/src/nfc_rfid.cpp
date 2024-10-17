#include <Wire.h>
#include <Adafruit_PN532.h>
#include <Preferences.h>
#include "entradas.h"

#define SDA_PIN 21
#define SCL_PIN 22
unsigned long numericUID = 0;
int i_posicao = 0;


Adafruit_PN532 nfc(SDA_PIN, SCL_PIN);
Preferences preferences;
const int maxUIDs = 2;
bool memoriaCheia = true;
bool duplicado;

void inicializa_nfc()
{
    Serial.begin(115200);
    Serial.println("Ola!");

    nfc.begin();

    uint32_t versiondata = nfc.getFirmwareVersion();
    if (!versiondata)
    {
        Serial.print("Não foi possível encontrar o PN53x");
        while (1)
            ;
    }

    nfc.SAMConfig();
    Serial.println("Esperando um cartão NFC...");

    // Inicia o NVS
    preferences.begin("UIDs", false);
}

bool isDuplicateUID(unsigned long newUID)
{
    for (int i = 0; i < maxUIDs; i++)
    {
        unsigned long storedUID = preferences.getULong(String(i).c_str(), 0); 
        if (storedUID == newUID)
        {
            return duplicado = true;
        }
    }
    return duplicado = false;
}

void clearMemoryIfAllowed()
{
    if (memoriaCheia)
    {
        Serial.println("Precione o botão NFC para continuar com a exclusao dos dados...");
        if (botao_pressionado_nfc())

        Serial.println("Botão pressionado. Limpando a memória...");

        // Limpa a memória flash
        preferences.clear();
        preferences.end();

        // Reinicia as preferências
        preferences.begin("UIDs", false);

        // Mensagem de confirmação
        Serial.println("Memória foi limpa.");
        memoriaCheia = false; // Redefinir o estado de memória cheia
    }
}

void storeUID(unsigned long newUID)
{

    for (i_posicao = 0; i_posicao < maxUIDs; i_posicao++)
    {
        unsigned long storedUID = preferences.getULong(String(i_posicao).c_str(), 0);
        if (storedUID == 0)
        {
            preferences.putULong(String(i_posicao).c_str(), newUID);
            Serial.print("UID armazenado na posição ");
            Serial.println(i_posicao);
            memoriaCheia = false;
            break;
        }
    }

    if (memoriaCheia)
    {
        clearMemoryIfAllowed();
    }
}

void atualiza_nfc()
{
    uint8_t success;
    uint8_t uid[] = {0, 0, 0, 0, 0, 0, 0};
    uint8_t uidLength;

    success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);

    if (success)
    {
        numericUID = 0;

        for (byte i = 0; i < uidLength; i++)
        {
            numericUID = numericUID * 256 + uid[i];
        }

        Serial.print("UID: ");
        Serial.println(numericUID);

        if (isDuplicateUID(numericUID))
        {
            Serial.println("UID duplicado detectado!");
        }
        else
        {
            Serial.println("Novo UID detectado.");
            storeUID(numericUID);
        }

        delay(1000);
    }
}
