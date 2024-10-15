#include <preferences.h>
#include "nfc_rfid.h"

Preferences preferences;
int i;

void biblioteca()
{
    preferences.begin("UIDs", false);
}

int atualiza_nvs()
{
    preferences.putULong(String(i).c_str(), newUID);
    // return newUID;
}

void clear()
{
    preferences.clear();
}

void end()
{
    preferences.end();
}

int save()
{
    preferences.getULong(String(i).c_str(), 0);
    // return i;
}