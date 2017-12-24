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

#include "p_init.h"

#include "p_states.h"
#include "p_sensors.h"
#include "p_solenoids.h"

#include "plc_inputs.h"
#include "plc_outputs.h"
#include "plc_lcd.h"
#include "plc_settings.h"

#include <Arduino.h>

void initEnter()
{
    if ( enableTimings )
    {
        plcEnableStatesTimeout();
    }
    else
    {
        plcDisableStatesTimeout();
    }
    initPlcOutputs();
    g_lcd.clear();
    g_lcd.setCursor(0,0);
    g_lcd.print("HACTPOUKA ...");
    plcSetFaultJump( STATE_FAULT );
    tone(8, 200, 500);
    delay(1000);
    tone(8, 200, 500);
    delay(1000);
    tone(8, 200);
    delay(500);
    noTone(8);
    if (plcInputRead(SENSOR_REMOVED) == LOW)
    {
        writePlcOutput( SOLENOID_REMOVE, HIGH );
    }
    if (plcInputRead(SENSOR_TOP) == LOW)
    {
        writePlcOutput( SOLENOID_UP, HIGH );
    }
    plcResetTime();
}

void initRun()
{
    uint8_t passed = 0;
    if (plcInputRead(SENSOR_TOP) == HIGH)
    {
        writePlcOutput( SOLENOID_UP, LOW );
        passed++;
    }
    if (plcInputRead(SENSOR_REMOVED) == HIGH)
    {
        writePlcOutput( SOLENOID_REMOVE, LOW );
        passed++;
    }
    if ( passed == 2 )
    {
        plcChangeState( STATE_REMOVE_BRIQUETTE );
    }
}

void initExit()
{
    writePlcOutput( SOLENOID_REMOVE, LOW );
    writePlcOutput( SOLENOID_UP, LOW );
    g_lcd.clear();
    g_lcd.noBacklight();
}

