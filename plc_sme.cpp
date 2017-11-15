#include "plc_sme.h"

#include "plc_inputs.h"
#include "plc_outputs.h"

#include <Arduino.h>

static uint32_t s_timestamp = 0;
static uint8_t  s_faultStateId = 0;
static SState *s_states;
static SState *s_active = nullptr;
static uint8_t s_count;

bool plcInitSme(SState *states, uint8_t count)
{
    if (!count) return false;
    s_states = states;
    s_count = count;
    plcChangeState( 0 );
    return true;
}

void plcRunSme()
{
/*    if ((s_active->timeout) && (millis() - s_timestamp > s_active->timeout))
    {
        plcChangeState( s_faultStateId );
    }
    else*/
    {
        s_active->state();
    }
}

void plcChangeState( uint8_t newState )
{
    if ( newState >= s_count )
    {
        return;
    }
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

void plcSetFaultState(uint8_t id)
{
    s_faultStateId = id;
}
