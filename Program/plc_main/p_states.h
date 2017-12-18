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
