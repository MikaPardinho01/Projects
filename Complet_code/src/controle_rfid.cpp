#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>
#include "controle_rfid.h"
#include "tempo.h"

//**Definições*/
#define SS_PIN 5
#define RST_PIN 2
#define DEBUG false
#define UID1 669071206
#define UID3 3488487708

unsigned long time_previous = 1000;
unsigned long intervalo = 0;

float uids;

//**Objetos*/
MFRC522 mfrc522(SS_PIN, RST_PIN); // Criar instância do MFRC522

//**Configuração*/
void inicializa_RFID()
{
    Serial.begin(9600);
    SPI.begin();
    mfrc522.PCD_Init();
}

void atualiza_RFID()
{
    if (millis() - time_previous >= intervalo)
    {
        unsigned long uid = lerRFID();

        if (DEBUG)
        {
            Serial.println("Aproxime o cartão do leitor");
            if (uid == 0)
            {
                Serial.println("Cartão não encontrado");
            }
            if (uid == 1)
            {
                Serial.println("Erro ao ler cartão");
            }
        }

        if (uid > 1)
        {
            Serial.print("UID: ");
            Serial.println(uid);

            switch (uid)
            {
            case UID1:
                Serial.println("Produto Cadastrado");
                // u8g2.clearBuffer();
                // u8g2.drawRFrame(0, 0, 126, 62, 2);
                // u8g2.setFont(u8g2_font_efraneextracondensed_te);
                // u8g2.drawStr(15, 25, "Acesso liberado");
                // u8g2.sendBuffer();
                break;

            case UID3:
                Serial.println("Produto Cadastrado");
                // u8g2.clearBuffer();
                // u8g2.drawRFrame(0, 0, 126, 62, 2);
                // u8g2.setFont(u8g2_font_efraneextracondensed_te);
                // u8g2.drawStr(15, 25, "Acesso liberado");
                // u8g2.sendBuffer();
                break;
            }
        }
        time_previous = millis();
    }
}

unsigned long lerRFID()
{
    if (!mfrc522.PICC_IsNewCardPresent())
    {
        return 0;
    }

    if (!mfrc522.PICC_ReadCardSerial())
    {
        return 1;
    }

    unsigned long numericUID = 0;
    for (byte i = 0; i < mfrc522.uid.size; i++)
    {
        numericUID = numericUID * 256 + mfrc522.uid.uidByte[i];
    }

    return numericUID;
}