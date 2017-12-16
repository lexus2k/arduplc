#include "p_diag.h"

#include "p_solenoids.h"
#include "p_states.h"
#include "p_sensors.h"
#include "plc_inputs.h"
#include "plc_outputs.h"
#include "plc_lcd.h"
#include "plc_buttons.h"
#include "plc_settings.h"
#include "plc_sme.h"

#include <Arduino.h>
#include <Wire.h>


static void plc_print_status()
{
    char str[16] = "- - - - - - -";
    g_lcd.setCursor(0, 0);
    g_lcd.print("I 1 2 3 4 5 6 7");
    for(uint8_t i=0; i<plcInputsCount();i++)
    {
       str[i*2] = (readPlcInput(i) == HIGH) ? '*' : '-';
    }
    g_lcd.setCursor(2, 1);
    g_lcd.print(str);
}

static uint8_t s_output = 0;

static void plc_change_output()
{
    if (plcStateTime() > 2000)
    {
        writePlcOutput(s_output, LOW);
        plcResetTime();
        s_output++;
        if (s_output >= plcOutputsCount()) s_output = 0;
        writePlcOutput(s_output, HIGH);
    }
}

void diagEnter()
{
    g_lcd.clear();
    plcResetTime();
    s_output = 0;
    if (!manualModeDiag)
    {
        writePlcOutput(s_output, HIGH);
    }
}

void diagRun()
{
    plc_print_status();
    if (manualModeDiag)
    {
        writePlcOutput( SOLENOID_UP, (g_buttons.isButtonDown( PLC_BUTTON_UP) &&
                                     (readPlcInput(SENSOR_TOP) == LOW) ) ? HIGH : LOW );
        writePlcOutput( SOLENOID_DOWN, (g_buttons.isButtonDown( PLC_BUTTON_DOWN) &&
                                     (readPlcInput(SENSOR_BOTTOM) == LOW)) ? HIGH : LOW );
        writePlcOutput( SOLENOID_REMOVE, (g_buttons.isButtonDown( PLC_BUTTON_RIGHT) &&
                                     (readPlcInput(SENSOR_REMOVED) == LOW)) ? HIGH : LOW );
        writePlcOutput( SOLENOID_PULL_OUT, (g_buttons.isButtonDown( PLC_BUTTON_LEFT) &&
                                     (readPlcInput(SENSOR_PULLED) == LOW))  ? HIGH : LOW );
    }
    else
    {
        plc_change_output();
    }
    if (g_buttons.isShortPress(PLC_BUTTON_SELECT))
    {
        plcChangeState( STATE_MAIN_MENU );
    }
}

void diagExit()
{
}

