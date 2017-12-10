
#pragma once

#include "tiny_buttons.h"

enum
{
    PLC_BUTTON_RIGHT    = 0,
    PLC_BUTTON_UP       = 1,
    PLC_BUTTON_DOWN     = 2,
    PLC_BUTTON_LEFT     = 3,
    PLC_BUTTON_SELECT   = 4,
};

extern TinyAnalogButtons g_buttons;

void plcInitButtons();