#include <preferences.h>
#include "nfc_rfid.h"

Preferences preferences;

void inicializa_biblioteca()
{
    preferences.begin("UIDs", false);
}

void atualiza_nvs()
{
    preferences.putULong(String(i).c_str(), newUID);
}

void clear()
{
    preferences.clear();
}

void end()
{
    preferences.end();
}

void save()
{
    preferences.getULong(String(i).c_str(), 0);
}