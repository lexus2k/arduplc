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

#include "plc_sme.h"

#include "plc_inputs.h"
#include "plc_outputs.h"

#include <Arduino.h>

static uint32_t s_timestamp = 0;
static uint8_t  s_faultJumpId = 0;
static uint8_t  s_faultedStateId = 0;
static SState *s_states;
static SState *s_active = nullptr;
static uint8_t s_count;
static bool    s_useTimeouts = true;

bool plcInitSme(SState *states, uint8_t count, uint8_t initalState)
{
    if (!count) return false;
    s_states = states;
    s_count = count;
    plcChangeState( initalState );
    return true;
}

void plcRunSme()
{
    if ((s_active->timeout) && (millis() - s_timestamp > s_active->timeout) && (s_useTimeouts))
    {
        s_faultedStateId = s_active->id;
        plcChangeState( s_faultJumpId );
    }
    else
    {
        s_active->state();
    }
}


void plcFault()
{
    s_faultedStateId = s_active->id;
    plcChangeState( s_faultJumpId );
}


void plcEnableStatesTimeout()
{
    s_useTimeouts = true;
}


void plcDisableStatesTimeout()
{
    s_useTimeouts = false;
}


void plcChangeState( uint8_t newState )
{
    if ( s_active != nullptr )
    {
        if ( s_active->exit )
        {
            s_active->exit();
        }
    }
    for (uint8_t i=0; i<s_count; i++)
    {
        if (s_states[i].id == newState)
        {
            s_active = &s_states[i];
            break;
        }
    }
    if ( s_active != nullptr )
    {
        if (s_active->init)
        {
            s_active->init();
            s_timestamp = millis();
        }
    }
}

uint32_t plcStateTime()
{
    return millis() - s_timestamp;
}

void plcResetTime()
{
    s_timestamp = millis();
}

void plcSetFaultJump(uint8_t id)
{
    s_faultJumpId = id;
}

uint8_t plcGetState()
{
    return s_active->id;
}

SState * plcGetFaultInfo()
{
    for (uint8_t i=0; i<s_count; i++)
    {
        if (s_states[i].id == s_faultedStateId)
        {
            return &s_states[i];
        }
    }
    return nullptr;
}
