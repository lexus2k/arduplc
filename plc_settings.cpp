#include "plc_settings.h"
#include "plc_sme.h"

#ifndef PLC_DEBUG

uint16_t shakeDelayMs = 100;
uint8_t  shakeCount   = 3;
uint16_t middleDelayMs = 200;
uint16_t pressDelayMs = 5000;

#else

uint16_t shakeDelayMs = 1000;//100;
uint8_t  shakeCount   = 3;
uint16_t middleDelayMs = 200; //200;
uint16_t pressDelayMs = 5000;

#endif
