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

#include "p_up.h"

#include "p_states.h"
#include "p_sensors.h"
#include "p_solenoids.h"

#include "plc_inputs.h"
#include "plc_outputs.h"
#include "plc_lcd.h"
#include "plc_settings.h"

#include <Arduino.h>

//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

void upEnter()
{
    g_lcd.clear();
    g_lcd.setCursor(0,0);
    g_lcd.print("BBEPX ...");
    plcResetTime();
    if (readPlcInput( SENSOR_TOP ) == LOW)
    {
        writePlcOutput( SOLENOID_UP, HIGH );
    }
}

void upRun()
{
    if (readPlcInput( SENSOR_TOP ) == HIGH)
    {
        g_stats.cycles++;
        if (automaticMode)
        {
            plcChangeState( STATE_REMOVE_BRIQUETTE );
        }
        else
        {
            plcChangeState( STATE_MAIN_MENU );
        }
    }
}

void upExit()
{
    writePlcOutput( SOLENOID_UP, LOW );
    if (!automaticMode)
    {
        /* Play pause melody */
        tone(8, 200); delay(300);
        tone(8, 500); delay(200);
        tone(8, 1000); delay(100);
        noTone(8);
    }
}

//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

void upCenterEnter()
{
    g_lcd.clear();
    g_lcd.setCursor(0,0);
    g_lcd.print("BBEPX uEHTP ...");
    plcResetTime();
    if (readPlcInput( SENSOR_MIDDLE ) == LOW)
    {
        writePlcOutput( SOLENOID_UP, HIGH );
    }
}

void upCenterRun()
{
    if (readPlcInput( SENSOR_MIDDLE ) == HIGH)
    {
        g_shakes = shakeCount + 1;
        g_finalPress = true;
        delay(middleDelayMs);
        writePlcOutput( SOLENOID_UP, LOW );
        plcChangeState( STATE_SHAKE_LEFT );
    }
    if (readPlcInput( SENSOR_TOP ) == HIGH)
    {
        plcFault();
    }
}

void upCenterExit()
{
    writePlcOutput( SOLENOID_UP, LOW );
    g_lcd.setCursor(0,0);
    g_lcd.print("CbIPbE ...");
}

