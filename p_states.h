#pragma once

#include "plc_sme.h"

#include <stdint.h>

enum
{
    STATE_POWER_ON,
    STATE_INIT,
    STATE_REMOVE_BRIQUETTE,
    STATE_DOWN_CENTER,
    STATE_SHAKE_RIGHT,
    STATE_SHAKE_LEFT,
    STATE_REMOVE,
    STATE_DOWN_TEMP,
    STATE_UP_MIDDLE,

    STATE_FAULT,
    STATE_PLC_DIAG,
    STATE_MAX,
};

extern uint8_t g_shakes;

extern SState programStates[];
