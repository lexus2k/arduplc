#pragma once

#include <stdint.h>

typedef struct
{
    uint16_t cycles;
} SPlcStats;


extern uint16_t shakeDelayMs;
extern uint8_t  shakeCount;
extern uint16_t middleDelayMs;
extern uint16_t pressDelayMs;
extern uint8_t  automaticMode;
extern uint8_t  prePressingMode;
extern uint8_t  manualModeDiag;
extern SPlcStats g_stats;


void saveSettings();
void loadSettings();
