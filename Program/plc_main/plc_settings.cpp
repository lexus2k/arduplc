#include "plc_settings.h"
#include "plc_sme.h"
#include <EEPROM.h>


#ifndef PLC_DEBUG

uint16_t shakeDelayMs = 100;
uint8_t  shakeCount   = 3;
uint16_t middleDelayMs = 200;
uint16_t pressDelayMs = 5000;
uint8_t  automaticMode = 0;
uint8_t  prePressingMode = 1;

#else

uint16_t shakeDelayMs = 1000;//100;
uint8_t  shakeCount   = 3;
uint16_t middleDelayMs = 200; //200;
uint16_t pressDelayMs = 5000;
uint8_t  automaticMode = 0;
uint8_t  prePressingMode = 1;

#endif

uint8_t  manualModeDiag = 0;

void saveSettings()
{
    EEPROM.put(0x10, shakeDelayMs);
    EEPROM.put(0x14, middleDelayMs);
    EEPROM.put(0x18, pressDelayMs);
    EEPROM.put(0x20, shakeCount);
    EEPROM.put(0x21, automaticMode);
    EEPROM.put(0x22, prePressingMode);
}

void loadSettings()
{
    uint8_t val8;
    uint16_t val16;
    EEPROM.get(0x10, val16); if (val16 != 0xFFFF) shakeDelayMs = val16;
    EEPROM.get(0x14, val16); if (val16 != 0xFFFF) middleDelayMs = val16;
    EEPROM.get(0x18, val16); if (val16 != 0xFFFF) pressDelayMs = val16;
    EEPROM.get(0x20, val8); if (val8 != 0xFF) shakeCount = val8;
    EEPROM.get(0x21, val8); if (val8 != 0xFF) automaticMode = val8;
    EEPROM.get(0x22, val8); if (val8 != 0xFF) prePressingMode = val8;
}
