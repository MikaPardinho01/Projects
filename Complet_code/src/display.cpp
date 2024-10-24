#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define SCREEN_ADDRESS 0x3C
#define OLED_RESET -1

Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const unsigned char Untitled[] PROGMEM = {
    // 'Untitled', 68x68px
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0x80, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x1f, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x1e, 0x00, 0x0c, 0xc1, 0x86, 0x13, 0x00, 0x07, 0x80, 0x1e,
    0x7f, 0xcc, 0x03, 0x80, 0x47, 0x3f, 0xe7, 0x80, 0x1e, 0x7f, 0xcc, 0x07, 0x80, 0x4f, 0x3f, 0xe7,
    0x80, 0x1e, 0x40, 0xcc, 0xe7, 0xe7, 0x83, 0x30, 0x27, 0x80, 0x1e, 0x40, 0xcc, 0xe7, 0xe7, 0x83,
    0x30, 0x27, 0x80, 0x1e, 0x40, 0xcf, 0xde, 0x00, 0x4f, 0x30, 0x27, 0x80, 0x1e, 0x40, 0xcf, 0x01,
    0xf9, 0x8f, 0x30, 0x27, 0x80, 0x1e, 0x40, 0xcf, 0x01, 0xf9, 0x8f, 0x30, 0x27, 0x80, 0x1e, 0x7f,
    0xcc, 0x39, 0x81, 0x9f, 0x3f, 0xe7, 0x80, 0x1e, 0x00, 0x0c, 0x99, 0x91, 0x9b, 0x00, 0x07, 0x80,
    0x1e, 0x00, 0x0c, 0xd9, 0x99, 0x93, 0x00, 0x07, 0x80, 0x1f, 0xff, 0xfc, 0xe0, 0x01, 0xcf, 0xff,
    0xff, 0x80, 0x1f, 0xff, 0xfc, 0xe0, 0x01, 0xcf, 0xff, 0xff, 0x80, 0x1f, 0xc0, 0xcc, 0x1f, 0x87,
    0x9c, 0x0f, 0x07, 0x80, 0x1f, 0xc3, 0x30, 0x19, 0x98, 0x7c, 0xc0, 0x27, 0x80, 0x1f, 0xc3, 0x30,
    0x19, 0x98, 0x7c, 0xc0, 0x27, 0x80, 0x1f, 0x9c, 0x0c, 0xff, 0xff, 0xfc, 0x03, 0x3f, 0x80, 0x1f,
    0x80, 0x00, 0x7f, 0xff, 0xf8, 0x00, 0x1f, 0x80, 0x1f, 0xc3, 0xf0, 0x3f, 0xff, 0xf0, 0x00, 0xdf,
    0x80, 0x1f, 0x90, 0x00, 0xff, 0xff, 0xf0, 0xcf, 0x07, 0x80, 0x1f, 0x90, 0x00, 0xff, 0xff, 0xf0,
    0xcf, 0x07, 0x80, 0x1f, 0xc3, 0x33, 0xff, 0xff, 0xc0, 0x30, 0xc7, 0x80, 0x1e, 0x7c, 0xcc, 0x3f,
    0xff, 0xf0, 0x0f, 0xff, 0x80, 0x1e, 0x7c, 0xcc, 0x3f, 0xff, 0xf0, 0x0f, 0xff, 0x80, 0x1e, 0x4f,
    0x30, 0xff, 0xff, 0xff, 0xf0, 0xff, 0x80, 0x1e, 0x4f, 0x20, 0xff, 0xff, 0xff, 0xf0, 0xff, 0x80,
    0x1e, 0x4f, 0x03, 0x3c, 0xf3, 0xf3, 0xcc, 0x07, 0x80, 0x1e, 0x7c, 0xff, 0xff, 0xff, 0xf3, 0x03,
    0x07, 0x80, 0x1e, 0x7c, 0xff, 0xff, 0xff, 0xf3, 0x03, 0x07, 0x80, 0x1e, 0x4c, 0x03, 0x3f, 0xff,
    0xf3, 0x3c, 0x3f, 0x80, 0x1e, 0x40, 0x78, 0x9e, 0x1f, 0xff, 0x3f, 0x87, 0x80, 0x1e, 0x40, 0xfc,
    0xde, 0x1f, 0xff, 0x3f, 0xc7, 0x80, 0x1e, 0x73, 0x0c, 0xe1, 0x81, 0xc0, 0x03, 0x3f, 0x80, 0x1e,
    0x73, 0x0c, 0xe1, 0x81, 0xc0, 0x03, 0x3f, 0x80, 0x1f, 0xff, 0xfc, 0x01, 0x87, 0x83, 0xf0, 0xc7,
    0x80, 0x1e, 0x00, 0x0f, 0x23, 0xe7, 0xc3, 0x33, 0xff, 0x80, 0x1e, 0x00, 0x0f, 0x27, 0xe7, 0xc3,
    0x33, 0xff, 0x80, 0x1e, 0x7f, 0xcf, 0xff, 0xe6, 0x03, 0xf0, 0xdf, 0x80, 0x1e, 0x7f, 0xcf, 0xff,
    0xe6, 0x01, 0xf0, 0x8f, 0x80, 0x1e, 0x40, 0xcc, 0x38, 0x06, 0x70, 0x00, 0x27, 0x80, 0x1e, 0x40,
    0xcc, 0x07, 0x81, 0xe0, 0xcc, 0x3f, 0x80, 0x1e, 0x40, 0xcc, 0x07, 0x81, 0xc0, 0xcc, 0x3f, 0x80,
    0x1e, 0x40, 0xcc, 0x27, 0x87, 0x80, 0x00, 0x1f, 0x80, 0x1e, 0x7f, 0xcf, 0x88, 0x07, 0xc7, 0xf0,
    0x9f, 0x80, 0x1e, 0x7f, 0xcf, 0xd8, 0x07, 0xcf, 0xf0, 0xdf, 0x80, 0x1e, 0x00, 0x0f, 0xc7, 0xf8,
    0x4f, 0x33, 0x3f, 0x80, 0x1e, 0x00, 0x0f, 0xc7, 0xf8, 0x6f, 0x33, 0x3f, 0x80, 0x1f, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x0f,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x84, 0x88,
    0xc8, 0x46, 0x80, 0x00, 0x00, 0x00, 0x00, 0x88, 0x08, 0x20, 0x20, 0x80, 0x00, 0x00, 0x00, 0x00,
    0x68, 0x04, 0x30, 0x28, 0x80, 0x00, 0x00, 0x00, 0x00, 0x10, 0x04, 0x18, 0x10, 0x80, 0x00, 0x00,
    0x00, 0x00, 0xa2, 0x22, 0x80, 0x16, 0x90, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00};

void inicializa_oled()
{
    oled.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
}

void atualiza_oled()
{
    oled.clearDisplay();
    oled.drawBitmap(0, 0, Untitled, 128, 64, WHITE);
    oled.display();
}
