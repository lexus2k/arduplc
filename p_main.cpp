#include "p_states.h"
#include "p_init.h"
#include "plc_diag.h"
#include "plc_poweron.h"
#include "plc_sme.h"

#include <Arduino.h>

SState programStates[/*STATE_MAX*/] =
{
    { STATE_POWER_ON, powerOnEnter, powerOnRun, nullptr },
    { STATE_INIT, initEnter, initRun, initExit },
//    { STATE_INIT_CYCLE, nullptr, initCycle },
//    { STATE_PRESS_MIDDLE, nullptr, pressToMiddle },
//    { STATE_PLATFORM_LEFT, nullptr, platformLeft },
//    { STATE_PLATFORM_LEFT_WAIT, nullptr, platformLeftWait },
//    { STATE_PLATFORM_RIGHT, nullptr, platformRight },
//    { STATE_PLATFORM_REMOVE, nullptr, platformRemove },
//    { STATE_PRESS_DOWN, nullptr, pressDown },
//    { STATE_PRESS_DOWN_WAIT, nullptr, pressDownWait },
//    { STATE_PRESS_UP, nullptr, pressUp },
//    { STATE_FAULT, nullptr, pressFault },
//    { STATE_REMOVE_BRIQUETTE, nullptr, removeBriquette },
    { STATE_PLC_DIAG, plc_manual_diag_enter, plc_manual_diag, nullptr },
};
