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

#include "plc_engine.h"
#include "plc_inputs.h"
#include "plc_outputs.h"

#include <Arduino.h>

#define TINY_STATE(id,name,func,minTimeout,maxTimeout)  \
     {id, name, func ## Enter, func ## Run, func ## Exit, minTimeout, maxTimeout}

typedef struct 
{
    uint8_t id;
    const char *name;
    void    (*init)();
    void    (*state)();
    void    (*exit)();
    uint32_t minTimeout;
    uint32_t maxTimeout;
} SState;

typedef struct
{
 
    SState *state;
    uint8_t data;
} SFaultInfo;

bool plcInitSme(SState *states, uint8_t count, uint8_t initalState);

void plcRunSme();

/**
 * Changes SM state. If current state has minimum defined timeout, and
 * state change take place, SME will check if minimum timeout is passed.
 * If not SME will switch to fault state.
 */
void plcChangeState( uint8_t newState );

/**
 * Changes SM state, regardless of timings set for the current state
 */
void plcForceChangeState( uint8_t newState );

void plcFault(uint8_t data=0);

void plcEnableStatesTimeout();

void plcDisableStatesTimeout();

uint8_t plcGetState();

void plcSetFaultJump(uint8_t id);

SFaultInfo plcGetFaultInfo();

uint32_t plcStateTime();

void plcResetTime();
