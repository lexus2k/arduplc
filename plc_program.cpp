#if 0

#include "states.h"
#include "sensors.h"
#include "solenoids.h"

#include "plc_engine.h"
#include "plc_inputs.h"
#include "plc_outputs.h"
#include "plc_diag.h"
#include "plc_poweron.h"
#include "plc_sme.h"

#include <Arduino.h>


// ==================================================================================
static bool platformRemoved;

static void pressSetup()
{
    platformRemoved = false;
}


static void pressInit()
{
    int result;
    if ( !platformRemoved )
    {
        result = plcActivateOutputUntil( OUTPUT_PLATFORM_REMOVE, INPUT_PLATFORM_OFF, 2000 );
        if (result < 0)
        {
            plcChangeState( STATE_FAULT );
            return;
        }
        platformRemoved = result != 0;
    }
    result = plcActivateOutputUntil( OUTPUT_PRESS_UP, INPUT_PRESS_HIGH, 10000 );
    if (result < 0)
    {
        plcChangeState( STATE_FAULT );
        return;
    }
    plcChangeStateCond( STATE_INIT_CYCLE, platformRemoved && (result == 1) );
    return;
}

// ==================================================================================
static uint8_t s_loadStepsLeft = 0;

static void initCycle()
{
    s_loadStepsLeft = 2;
    plcChangeState( STATE_PRESS_MIDDLE );
}

// ==================================================================================
static void pressToMiddle()
{
    int result = plcActivateOutputUntil( OUTPUT_PRESS_DOWN, INPUT_PRESS_MID, 7000 );
    if (result < 0)
    {
        plcChangeState( STATE_FAULT );
        return;
    }
    plcChangeStateCond( STATE_PLATFORM_LEFT, result != 0 );
}

// ==================================================================================
static void platformLeft()
{
    int result = plcActivateOutputUntil( OUTPUT_PLATFORM_PLACE, INPUT_PLATFORM_ON, 2000 );
    if ( result < 0 )
    {
        plcChangeState( STATE_FAULT );
        return;
    }
    plcChangeStateCond( STATE_PLATFORM_LEFT_WAIT, result != 0 );
}

// ==================================================================================
static void platformLeftWait()
{
    if (plcTimeout(500))
    {
        s_loadStepsLeft--;
        if ( s_loadStepsLeft == 0)
        {
            plcChangeState( STATE_PLATFORM_REMOVE );
        }
        else
        {
            plcChangeState( STATE_PLATFORM_RIGHT );
        }
    }
}

// ==================================================================================
static void platformRight()
{
    int result = plcActivateOutputUntil( OUTPUT_PLATFORM_REMOVE, INPUT_PLATFORM_OFF, 600 );
    plcChangeStateCond( STATE_PLATFORM_LEFT, result != 0);
}

// ==================================================================================
static void platformRemove()
{
    int result = plcActivateOutputUntil( OUTPUT_PLATFORM_REMOVE, INPUT_PLATFORM_OFF, 2000 );
    if ( result < 0 )
    {
        plcChangeState( STATE_FAULT );
        return;
    }
    plcChangeStateCond( STATE_PRESS_DOWN, result != 0);
}

// ==================================================================================
static void pressDown()
{
    int result = plcActivateOutputUntil( OUTPUT_PRESS_DOWN, INPUT_PRESS_MID, 10000 );
    if (result < 0)
    {
        plcChangeState( STATE_FAULT );
        return;
    }
    plcChangeStateCond( STATE_PRESS_DOWN_WAIT, result != 0 );
}

// ==================================================================================
static void pressDownWait()
{
    if (plcTimeout(600))
    {
        plcChangeState( STATE_PRESS_UP );
    }
}


// ==================================================================================
static void pressUp()
{
    int result = plcActivateOutputUntil( OUTPUT_PRESS_UP, INPUT_PRESS_HIGH, 10000 );
    if (result < 0)
    {
        plcChangeState( STATE_FAULT );
        return;
    }
    plcChangeStateCond( STATE_REMOVE_BRIQUETTE, result != 0 );
}

// ==================================================================================
static void removeBrequette()
{
    int result = plcActivateOutputUntil( OUTPUT_PLATFORM_PLACE, INPUT_PLATFORM_ON, 2000 );
    if ( result < 0 )
    {
        plcChangeState( STATE_FAULT );
        return;
    }
    plcChangeStateCond( STATE_INIT_CYCLE, result != 0 );
}

// ==================================================================================
static void pressFault()
{
    initPlcOutputs();
}

// ==================================================================================
static void removeBriquette()
{
}

// ==================================================================================

extern SState programStates[STATE_MAX] =
{
    { STATE_POWER_ON, powerOnEnter, powerOnRun },
    { STATE_INIT, pressSetup, pressInit },
    { STATE_INIT_CYCLE, nullptr, initCycle },
    { STATE_PRESS_MIDDLE, nullptr, pressToMiddle },
    { STATE_PLATFORM_LEFT, nullptr, platformLeft },
    { STATE_PLATFORM_LEFT_WAIT, nullptr, platformLeftWait },
    { STATE_PLATFORM_RIGHT, nullptr, platformRight },
    { STATE_PLATFORM_REMOVE, nullptr, platformRemove },
    { STATE_PRESS_DOWN, nullptr, pressDown },
    { STATE_PRESS_DOWN_WAIT, nullptr, pressDownWait },
    { STATE_PRESS_UP, nullptr, pressUp },
    { STATE_FAULT, nullptr, pressFault },
    { STATE_REMOVE_BRIQUETTE, nullptr, removeBriquette },
    { STATE_PLC_DIAG, plc_manual_diag_enter, plc_manual_diag },
};

#endif