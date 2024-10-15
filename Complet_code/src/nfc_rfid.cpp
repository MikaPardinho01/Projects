#include <Wire.h>
#include <Adafruit_PN532.h>
#include "memory.h"

#define SDA_PIN 21
#define SCL_PIN 22

Adafruit_PN532 nfc(SDA_PIN, SCL_PIN);

const int maxUIDs = 10;

void inicializa_nfc()
{
    Serial.begin(115200);
    Serial.println("Ola!");

    nfc.begin();

    uint32_t versiondata = nfc.getFirmwareVersion();
    if (!versiondata)
    {
        Serial.print("Não foi possível encontrar o PN53x");
        while (1); 
    }

    nfc.SAMConfig();
    Serial.println("Esperando um cartão NFC...");
    // biblioteca();
}

bool isDuplicateUID(unsigned long newUID)
{
    for (int i = 0; i < maxUIDs; i++)
    {
        unsigned long storedUID = (unsigned long)save();
        if (storedUID == newUID)
        {
            return true;
        }
    }
    return false;
}

void clearMemoryIfAllowed()
{
    Serial.println("Memória cheia! Deseja apagar todos os dados? (sim/não)");

    while (!Serial.available())
    {
    }

    String resposta = Serial.readStringUntil('\n');
    resposta.trim();

    if (resposta.equalsIgnoreCase("sim"))
    {
        Serial.println("Limpando a memória...");
        clear();
        end();
        biblioteca;
        Serial.println("Memória foi limpa.");
    }
    else
    {
        Serial.println("Memória mantida, nenhum dado foi excluído.");
    }
}

void storeUID(unsigned long newUID)
{
    bool memoriaCheia = true;

    for (int i = 0; i < maxUIDs; i++)
    {
        unsigned long storedUID = save();
        if (storedUID == 0)
        {
            atualiza_nvs();
            Serial.print("UID armazenado na posição ");
            Serial.println(i);
            memoriaCheia = false;
            break;
        }
    }

    if (memoriaCheia)
    {
        // Memoria cheia, deseja limpar?
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
        unsigned long numericUID = 0;

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
