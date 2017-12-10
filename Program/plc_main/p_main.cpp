#include "p_power_on.h"
#include "p_main_menu.h"
#include "p_init.h"
#include "p_diag.h"
#include "p_fault.h"
#include "p_shake_right.h"
#include "p_shake_left.h"
#include "p_down.h"
#include "p_up.h"

#include "p_states.h"

#include "plc_sme.h"

#include <Arduino.h>

uint8_t g_shakes;
bool g_finalPress;

SState programStates[] =
{
//            |        ID             |   NAME     |   FUNCTION        | TIMEOUT(MS)  |
    TINY_STATE(STATE_POWER_ON,         "powerOn",      powerOn,           0),
    TINY_STATE(STATE_INIT,             "init",         init,              10000),
    TINY_STATE(STATE_REMOVE_BRIQUETTE, "breq",         removeBriquette,   2000),
    TINY_STATE(STATE_DOWN_CENTER,      "center",       downCenter,        7000),
    TINY_STATE(STATE_SHAKE_RIGHT,      "right",        shakeRight,        1000),
    TINY_STATE(STATE_SHAKE_LEFT,       "left",         shakeLeft,         2000),
    TINY_STATE(STATE_REMOVE,           "rem",          remove,            2000),
    TINY_STATE(STATE_DOWN_TEMP,        "temp",         downTemp,          10000),
    TINY_STATE(STATE_UP_MIDDLE,        "upcnt",        upCenter,          10000),
    TINY_STATE(STATE_DOWN,             "down",         down,              10000),
    TINY_STATE(STATE_UP,               "up",           up,                10000),
    TINY_STATE(STATE_FAULT,            "ft",           fault,             0),
    TINY_STATE(STATE_MAIN_MENU,        "menu",         mainMenu,          0),
    TINY_STATE(STATE_PLC_DIAG,          "diag",        diag,              0),
};

uint8_t programStatesCount()
{
    return sizeof(programStates)/sizeof(SState);
}
