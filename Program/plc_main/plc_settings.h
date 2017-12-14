#pragma once

#include <stdint.h>

extern uint16_t shakeDelayMs;
extern uint8_t  shakeCount;
extern uint16_t middleDelayMs;
extern uint16_t pressDelayMs;
extern uint8_t  automaticMode;
extern uint8_t  prePressingMode;
extern uint8_t  manualModeDiag;

void saveSettings();
void loadSettings();
