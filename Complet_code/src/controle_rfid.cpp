#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>
#include "controle_rfid.h"
#include "tempo.h"

//**Definições*/
#define SS_PIN 5
#define RST_PIN 2
#define DEBUG false

// vetor(array) dos UIDS
unsigned long UIDS[4] =
    {
        669071206, 3488487708, 4282771230, 340843683};

// vetor(array) de UIDS ja lidos
unsigned long uidsLidos[10] = {0};
int UIDS_lidos = 0;

unsigned long time_previous = 1000;
unsigned long intervalo = 0;

//**Objetos*/
MFRC522 mfrc522(SS_PIN, RST_PIN); // Criar instância do MFRC522

//**Configuração*/
void inicializa_RFID()
{
    SPI.begin();
    mfrc522.PCD_Init();
}

//Verificação para UIDS duplicados
bool verificarDuplicado(unsigned long uid)
{
    for (int i = 0; i < UIDS_lidos; i++)
    {
        if (uidsLidos[i] == uid)
        {
            Serial.println("UID Duplicado"); // retorna true
            return true;
        }
    }
    Serial.println("UID nao duplicado");
    return false;
}

void atualiza_RFID()
{
    //Serial.println("funcao rfid");
    if (true)//millis() - time_previous >= intervalo)
    {
        unsigned long uid = lerRFID();
        Serial.printf("UID = %d \n\r", uid);
        if (DEBUG)        {
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

            bool produtoEncontrado = false;

            // Verificar se o UID lido está no array de UIDS
            for (int i = 0; i < 4; i++)
            {
                if (uid == UIDS[i])
                {
                    Serial.println("Produto Cadastrado");
                    produtoEncontrado = true;
                    break;
                }
            }

            // Se o produto nao foi encontrado
            if (!produtoEncontrado)
            {
                Serial.println("Produto não cadastrado");
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