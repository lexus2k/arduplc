#include "p_power_on.h"

#include "p_states.h"

#include "plc_inputs.h"
#include "plc_outputs.h"
#include "plc_settings.h"
#include "plc_lcd.h"
#include "plc_buttons.h"
#include "plc_sme.h"

void powerOnEnter()
{
    pinMode(8, OUTPUT); // sound
    initPlcInputs();
    initPlcOutputs();
    loadSettings();
    g_buttons.init();
    g_lcd.init();
    g_lcd.backlight();
    g_lcd.clear();
    g_lcd.setCursor(0, 0);
    g_lcd.print("Powering on...");
}

void powerOnRun()
{
    plcChangeState(STATE_MAIN_MENU);
}

void powerOnExit()
{
}
