#pragma once

#include "plc_engine.h"
#include "plc_inputs.h"
#include "plc_outputs.h"

#include <Arduino.h>

typedef struct 
{
    uint8_t id;
    void    (*init)();
    void    (*state)();
    void    (*exit)();
} SState;

bool plcInitSme(SState *states, uint8_t count);

void plcRunSme();

void plcChangeState( uint8_t newState );

bool plcTimeout(uint32_t timeout);

void plcResetTimer();
