/*
    Copyright (C) 2017 - 2018 Alexey Dynda

    This file is part of Ardu PLC project.

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "plc_settings.h"
#include "plc_sme.h"
#include <EEPROM.h>


uint16_t shakeMoveRightMs = 300;
uint16_t loadDelayMs  = 0;
uint8_t  shakeCount   = 3;
uint16_t pressDelayMs = 2000;
uint8_t  automaticMode = 0;
uint8_t  prePressingMode = 0;
uint8_t  enableTimings = 1;
uint8_t  manualModeDiag = 0;

SPlcStats g_stats = { 0 };

void saveSettings()
{
    EEPROM.put(0x10, shakeMoveRightMs);
    EEPROM.put(0x18, pressDelayMs);
    EEPROM.put(0x20, shakeCount);
    EEPROM.put(0x21, automaticMode);
    EEPROM.put(0x22, prePressingMode);
}

void loadSettings()
{
    uint8_t val8;
    uint16_t val16;
    EEPROM.get(0x10, val16); if (val16 != 0xFFFF) shakeMoveRightMs = val16;
    EEPROM.get(0x18, val16); if (val16 != 0xFFFF) pressDelayMs = val16;
    EEPROM.get(0x20, val8); if (val8 != 0xFF) shakeCount = val8;
    EEPROM.get(0x21, val8); if (val8 != 0xFF) automaticMode = val8;
    EEPROM.get(0x22, val8); if (val8 != 0xFF) prePressingMode = val8;
}
