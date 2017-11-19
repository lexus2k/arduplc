#include "p_fault.h"

#include "p_states.h"
#include "p_sensors.h"
#include "p_solenoids.h"

#include "plc_inputs.h"
#include "plc_outputs.h"
#include "plc_buttons.h"
#include "plc_lcd.h"

#include <Arduino.h>

void faultEnter()
{
    initPlcOutputs();
    g_lcd.clear();
    g_lcd.setCursor(0,0);
    g_lcd.print("!!! ERROR !!!");

    SState * state = plcGetFaultInfo();
    if (state != nullptr)
    {
        g_lcd.setCursor(0,1);
        g_lcd.print(state->name);
    }
    tone(8, 400, 500);
    delay(1000);
    tone(8, 400, 500);
    delay(1000);
    tone(8, 400);
    delay(500);
    noTone(8);
    plcResetTime();
}

void faultRun()
{
    if (g_buttons.isShortPress())
    {
        plcChangeState(STATE_MAIN_MENU);
    }
}

void faultExit()
{
}

