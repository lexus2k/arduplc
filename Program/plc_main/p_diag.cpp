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

static uint8_t s_up = LOW;
static uint8_t s_down = LOW;
static uint8_t s_remove = LOW;
static uint8_t s_pull_out = LOW;
static uint8_t s_common = LOW;

static void plc_print_status()
{
    char str[16] = "- - - - - - -";
    for(uint8_t i=0; i<plcInputsCount();i++)
    {
         int input = readPlcInput(i);
         str[i*2] = (input == HIGH) ? '*' : '-';
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
    s_up = LOW;
    s_down = LOW;
    s_pull_out = LOW;
    s_remove = LOW;
    s_common = LOW;
    g_lcd.clear();
    g_lcd.setCursor(0, 0);
    g_lcd.print("I 1 2 3 4 5 6 7");
    plcResetTime();
    s_output = 0;
    if (!manualModeDiag)
    {
        writePlcOutput(s_output, HIGH);
    }
}

void diagRun()
{
/*    int aa = analogRead( A3 );
    g_lcd.setCursor(0, 0);
    g_lcd.print(aa);
    g_lcd.print("   "); */

    plc_print_status();
    if (manualModeDiag)
    {
        uint8_t state;
        state = (g_buttons.isButtonDown( PLC_BUTTON_UP) && (readPlcInput(SENSOR_TOP) == LOW)) ? HIGH: LOW;
        if (s_up != state) writePlcOutput( SOLENOID_UP, state);
        s_up = state;

        state = (g_buttons.isButtonDown( PLC_BUTTON_DOWN) && (readPlcInput(SENSOR_BOTTOM) == LOW)) ? HIGH: LOW;
        if (s_down != state) writePlcOutput( SOLENOID_DOWN, state);
        s_down = state;

        state = (g_buttons.isButtonDown( PLC_BUTTON_RIGHT) && (readPlcInput(SENSOR_REMOVED) == LOW)) ? HIGH: LOW;
        if (s_remove != state) writePlcOutput( SOLENOID_REMOVE, state);
        s_remove = state;

        state = (g_buttons.isButtonDown( PLC_BUTTON_LEFT) && (readPlcInput(SENSOR_PULLED) == LOW)) ? HIGH: LOW;
        if (s_pull_out != state) writePlcOutput( SOLENOID_PULL_OUT, state);
        s_pull_out = state;

        state = LOW;
        if ((s_up == HIGH) || (s_down == HIGH) || (s_pull_out == HIGH) || (s_remove == HIGH))
        {
             state = HIGH;
        }
        if (s_common != state) writePlcOutput( SOLENOID_COMMON, state );
        s_common = state;
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
    initPlcInputs();
}

