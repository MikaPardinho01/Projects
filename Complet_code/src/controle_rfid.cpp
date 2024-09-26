//*----------------------------
//* RST/Reset   RST          02 //pode alterar
//* SPI SS      SDA(SS)      05 //pode alterar
//* SPI MOSI    MOSI         23
//* SPI MISO    MISO         19
//* SPI SCK     SCK          18
/*----------------------------

//**Bibliotecas*/
#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>
#include "controle_rfid.h"
#include "display.h"

//**Definições*/
#define SS_PIN 5
#define RST_PIN 2
#define DEBUG false

unsigned long tempo_definido = 0;
const unsigned long intervalo = 1000;
unsigned long uid;
int cadastro = 0;

//**Objetos*/
MFRC522 mfrc522(SS_PIN, RST_PIN); // Criar instância do MFRC522

//**Configuração*/
void inicializa_rfid()
{
    Serial.begin(9600);
    SPI.begin();
    mfrc522.PCD_Init();
}
/*
implementar um botao para gravar os dados lidos pelo RFID
Deste modo fazendo o controle do estoque e realizando o banco de dados
*/
void atualiza_rfid()
{
    if (millis() - tempo_definido >= intervalo)
    {
        uid = lerRFID();

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
    }
}

unsigned long lerRFID()
{
    // Procura por cartões RFID
    if (!mfrc522.PICC_IsNewCardPresent())
    {
        return 0;
    }

    // Seleciona um dos cartões
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