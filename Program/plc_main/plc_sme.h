#pragma once

#include "plc_engine.h"
#include "plc_inputs.h"
#include "plc_outputs.h"

#include <Arduino.h>

#define TINY_STATE(id,name,func,timeout)  \
     {id, name, func ## Enter, func ## Run, func ## Exit, timeout}

typedef struct 
{
    uint8_t id;
    char    *name;
    void    (*init)();
    void    (*state)();
    void    (*exit)();
    uint32_t timeout;
} SState;

bool plcInitSme(SState *states, uint8_t count, uint8_t initalState);

void plcRunSme();

void plcChangeState( uint8_t newState );

void plcFault();

uint8_t plcGetState();

void plcSetFaultState(uint8_t id);

SState * plcGetFaultInfo();

uint32_t plcStateTime();

void plcResetTime();
