#include "p_power_on.h"
#include "p_init.h"
#include "p_diag.h"
#include "p_fault.h"
#include "p_remove_briq.h"
#include "p_down_center.h"
#include "p_shake_right.h"
#include "p_shake_left.h"
#include "p_remove.h"
#include "p_down_temp.h"

#include "p_states.h"

#include "plc_sme.h"

#include <Arduino.h>

uint8_t g_shakes;

SState programStates[STATE_MAX] =
{
//            |        ID             |   NAME     |   FUNCTION        | TIMEOUT(MS)  |
    TINY_STATE(STATE_POWER_ON,         "powerOn",      powerOn,           0),
    TINY_STATE(STATE_INIT,             "init",         init,              10000),
    TINY_STATE(STATE_REMOVE_BRIQUETTE, "breq",         removeBriquette,   2000),
    TINY_STATE(STATE_DOWN_CENTER,      "center",       downCenter,        7000),
    TINY_STATE(STATE_SHAKE_RIGHT,      "right",        shakeRight,        1000),
    TINY_STATE(STATE_SHAKE_LEFT,       "right",        shakeLeft,         1000),
    TINY_STATE(STATE_REMOVE,           "rem",          remove,            2000),
    TINY_STATE(STATE_DOWN_TEMP,        "temp",         downTemp,          10000),
    TINY_STATE(STATE_FAULT,            nullptr,        fault,             0),
    TINY_STATE(STATE_PLC_DIAG,          "diag",        diag,              0),
};
