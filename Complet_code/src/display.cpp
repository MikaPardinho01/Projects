#include <Arduino.h>
#include <U8g2lib.h>
#include "temperatura.h"
#include "controle_rfid.h"

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);

void inicializa_u8g2()
{
    u8g2.begin();
}

void display_temperatura()
{
    u8g2.drawRFrame(3, 3, 122, 27, 5);
    u8g2.drawRFrame(3, 34, 122, 27, 5);
    u8g2.setFont(u8g2_font_unifont_t_weather);
    u8g2.drawGlyph(5, 23, 0x31);
    u8g2.drawGlyph(5, 53, 0x32);
    u8g2.setFont(u8g2_font_lubBI12_te);
    u8g2.drawStr(30, 23, String(lerTemperatura(), 1).c_str());
    u8g2.drawStr(70, 23, "*C");
    u8g2.drawStr(30, 53, String(lerUmidade(), 0).c_str());
    u8g2.drawStr(60, 53, "%");
}

void display_controle_rfid()
{
    if (uid > 1)
    {
        Serial.print("UID: ");
        Serial.println(uid);

        switch (uid)
        {
        case UID1:
            Serial.println("Cartão 1");
            u8g2.clearBuffer();
            u8g2.drawRFrame(0, 0, 126, 62, 2);
            u8g2.setFont(u8g2_font_efraneextracondensed_te);
            u8g2.drawStr(15, 25, "Produto cadastrado");
            u8g2.sendBuffer();
            break;

        case UID3:
            Serial.println("Cartão 3");
            u8g2.clearBuffer();
            u8g2.drawRFrame(0, 0, 126, 62, 2);
            u8g2.setFont(u8g2_font_efraneextracondensed_te);
            u8g2.drawStr(15, 25, "Produto cadastrado");
            u8g2.sendBuffer();
            break;

        default:
            u8g2.clearBuffer();
            u8g2.drawRFrame(0, 0, 126, 62, 2);
            u8g2.setFont(u8g2_font_efraneextracondensed_te);
            u8g2.drawStr(15, 25, "Produto não cadastrado");
            u8g2.sendBuffer();
            break;
        }
    }
}
