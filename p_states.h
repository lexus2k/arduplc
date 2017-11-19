#pragma once

#include "plc_sme.h"

#include <stdint.h>

enum
{
    STATE_POWER_ON,
    STATE_MAIN_MENU,
    STATE_PLC_DIAG,
    STATE_FAULT,

    STATE_PASSIVE,

    STATE_INIT,
    STATE_REMOVE_BRIQUETTE,
    STATE_DOWN_CENTER,
    STATE_SHAKE_RIGHT,
    STATE_SHAKE_LEFT,
    STATE_REMOVE,
    STATE_DOWN_TEMP,
    STATE_UP_MIDDLE,
    STATE_DOWN,
    STATE_UP,
};

extern uint8_t g_shakes;
extern bool g_finalPress;

extern SState programStates[];
uint8_t programStatesCount();
