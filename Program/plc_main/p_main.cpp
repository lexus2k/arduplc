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
    TINY_STATE(STATE_POWER_ON,         "pwr",          powerOn,           0),
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
