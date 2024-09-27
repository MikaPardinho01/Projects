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
#include <Servo.h>
#include <U8g2lib.h>
#include <Preferences.h> 

//**Definições*/
#define SS_PIN 5
#define RST_PIN 2
#define DEBUG false
#define UID1 669071206
#define UID3 3488487708

int produto;


//**Objetos*/
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);
MFRC522 mfrc522(SS_PIN, RST_PIN); // Criar instância do MFRC522
Preferences preferences;

//*Prototipos**/
unsigned long lerRFID(void);

void configuracao()

{
  produto = 669071206;
   preferences.putInt("Produto", produto);
   Serial.printf("Configuração Padrão, produto %d\n", produto);
}

void setup()
{
  u8g2.begin();
  Serial.begin(9600); // Iniciar comunicação serial
  SPI.begin();        // Iniciar SPI
  mfrc522.PCD_Init(); // Iniciar MFRC522
   preferences.begin("config", false);
    produto = preferences.getInt("produto", 669071206);
}


void loop()
{
  unsigned long uid = lerRFID();

  if (DEBUG)
  {
    Serial.println("Aproxime o cartão do leitor");
    if (uid == 0){
      Serial.println("Cartão não encontrado");
    }
    if (uid == 1){
      Serial.println("Erro ao ler cartão");
    }
  }


  if (produto == uid){
    Serial.print("UID: ");
    Serial.println(uid);

    switch (uid){
    case UID1:
      Serial.println("Produto Cadastrado");
      u8g2.clearBuffer();
      u8g2.drawRFrame(0, 0, 126, 62, 2); 
      u8g2.setFont(u8g2_font_efraneextracondensed_te);
      u8g2.drawStr(15, 25, "Produto cadastrado");
      u8g2.sendBuffer();
      break;

    // case UID3:
    //   Serial.println("Cartão 3");
    //   u8g2.clearBuffer();
    //   u8g2.drawRFrame(0, 0, 126, 62, 2); 
    //   u8g2.setFont(u8g2_font_efraneextracondensed_te);
    //   u8g2.drawStr(15, 25, "Produto cadastrado");
    //   u8g2.sendBuffer();
    // break;

    default:
      u8g2.clearBuffer();
      u8g2.drawRFrame(0, 0, 126, 62, 2); 
      u8g2.setFont(u8g2_font_efraneextracondensed_te);
      u8g2.drawStr(15, 25, "Produto não cadastrado");
      u8g2.sendBuffer();
      break;
    }
  }

  delay(1000); //!NAO USE DELAY EM HIPITESE ALGUMA
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