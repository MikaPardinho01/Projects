    #include <Wire.h>
    #include <Adafruit_PN532.h>
    #include <Preferences.h>
    // #include <api.h>

    #define SDA_PIN 21
    #define SCL_PIN 22

    unsigned long numericUID = 0;
    unsigned long anterior_tempo_nfc = 0;
    unsigned long def = 1000;

    Adafruit_PN532 nfc(SDA_PIN, SCL_PIN);
    Preferences preferences;

    const int maxUIDs = 2;
    bool memoriaCheia = false;
    bool duplicado = false;
    int i_posicao = 0;

    String pos;
    String mc;

    void inicializa_nfc()
    {
        Serial.begin(115200);
        Wire.begin(SDA_PIN, SCL_PIN);

        uint32_t versiondata = nfc.getFirmwareVersion();
        if (!versiondata)
        {
            Serial.print("Não foi possível encontrar o PN53x");
            while (1)
                ;
        }

        nfc.SAMConfig();
        Serial.println("Esperando um cartão NFC...");
        preferences.begin("UIDs", false);
    }

    bool isDuplicateUID(unsigned long newUID)
    {
        for (i_posicao = 0; i_posicao < maxUIDs; i_posicao++)
        {
            unsigned long storedUID = preferences.getULong(String(i_posicao).c_str(), 0);
            if (storedUID == newUID)
            {
                // duplicado = true;
                Serial.print("teste de nfc - verificando verdadeiro. . . . . . . . . . . . ..  . ");
                return duplicado = true;
            }
        }
        return duplicado = false;
        Serial.print("teste de nfc - verificando falso. . . . . . . . . . . . ..  . ");
    }

    void mensagem()
    {
        if (duplicado == true)
        {
            pos = "UID duplicado detectado na posição " + String(i_posicao) + "\n";
        }
        else if (duplicado == false)
        {
            pos = "Novo UID detectado na posição " + String(i_posicao) + "\n";
        }
        // else if (memoriaCheia == true)
        // // {
        // //     mc = "Memoria cheia. Limpando a memória..." + String(memoriaCheia) + "\n";
        // // }
    }

    void clearMemoryIfAllowed()
    {
        preferences.clear();
        preferences.begin("UIDs", false);
        memoriaCheia = false;
        i_posicao = 0;
    }

    bool storeUID(unsigned long newUID)
    {
        {
            if (isDuplicateUID(newUID))
            {
                Serial.println("UID já armazenado (duplicado).");
                return false;
            }

            if (i_posicao >= maxUIDs - 1)
            {
                memoriaCheia = true;
                clearMemoryIfAllowed(); 
            }

            i_posicao++;                                            
            preferences.putULong(String(i_posicao).c_str(), newUID); 
            Serial.printf("Novo UID armazenado na posição %d\n", i_posicao);

            i_posicao++;
            return true;
        }
        // for (i_posicao = 0; i_posicao <= maxUIDs; i_posicao++)
        // {
        //     unsigned long storedUID = preferences.getULong(String(i_posicao).c_str(), 0);
        //     if (storedUID == 0)
        //     {
        //         preferences.putULong(String(i_posicao).c_str(), newUID);
        //         preferences.end();
        //         Serial.printf("UID armazenado na posição %d\n", i_posicao);
        //         memoriaCheia = false;
        //         return true;
        //     }
        // }
        // memoriaCheia = true;
        // clearMemoryIfAllowed();
        // return false;
    }

    void atualiza_nfc()
    {
        if (millis() - anterior_tempo_nfc >= def)
        {
            anterior_tempo_nfc = millis();

            byte success;
            byte uid[] = {0, 0, 0, 0, 0, 0, 0};
            byte uidLength;

            success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength, 500);

            if (success)
            {
                numericUID = 0;

                for (byte i = 0; i < uidLength; i++)
                {
                    numericUID = numericUID * 256 + uid[i];
                    Serial.print(uid[i], HEX);
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
            }
        }
    }
