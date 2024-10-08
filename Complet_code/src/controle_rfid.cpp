#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>
#include "controle_rfid.h"
#include "tempo.h"

//**Definições*/
#define SS_PIN 5
#define RST_PIN 2
#define DEBUG false

//colocar dentro de um vetor(array)
#define UID1 669071206
#define UID2 3488487708
#define UID3 4282771230
#define UID4 340843683

int UID5 = 0;

unsigned long time_previous = 1000;
unsigned long intervalo = 0;


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

            switch (uid) //for it... switch dentro do for it)
            {
            case UID1:
                Serial.println("Produto Cadastrado");
                break;

            case UID2:
                Serial.println("Produto Cadastrado");
                break;

            case UID3:
                Serial.println("Produto Cadastrado");
                break;

            case UID4:
                Serial.println("Produto Cadastrado");
                break;

             default: // caso contrario, duplicado
                 //antes, criar uma função com a array para fazer a analise de duplicadas

                    
            }
        }
        
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
