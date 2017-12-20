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

#include "p_down.h"

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

void downTempEnter()
{
    g_lcd.clear();
    g_lcd.setCursor(0,1);
    g_lcd.print("Pre-press ...");
    plcResetTime();
    if (readPlcInput( SENSOR_BOTTOM_TEMP ) == LOW)
    {
        writePlcOutput( SOLENOID_DOWN, HIGH );
    }
}

void downTempRun()
{
    if (readPlcInput( SENSOR_BOTTOM_TEMP ) == HIGH)
    {
        plcChangeState( STATE_UP_MIDDLE );
    }
    if (readPlcInput( SENSOR_BOTTOM ) == HIGH)
    {
        plcFault();
    }
}

void downTempExit()
{
    writePlcOutput( SOLENOID_DOWN, LOW );
}


//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////


void downCenterEnter()
{
    g_lcd.clear();
    g_lcd.setCursor(0,0);
    g_lcd.print("BHU3 uEHTP ...");
    plcResetTime();
    if (readPlcInput( SENSOR_MIDDLE ) == LOW)
    {
        writePlcOutput( SOLENOID_DOWN, HIGH );
    }
}

void downCenterRun()
{
    if (readPlcInput( SENSOR_MIDDLE ) == HIGH)
    {
        plcChangeState( STATE_SHAKE_RIGHT );
        g_shakes = shakeCount + 1;
        if (prePressingMode)
        {
            g_finalPress = false;
        }
        else
        {
            g_finalPress = true;
        }
    }
    if (readPlcInput( SENSOR_BOTTOM ) == HIGH)
    {
        plcFault();
    }
}

void downCenterExit()
{
    writePlcOutput( SOLENOID_DOWN, LOW );
    g_lcd.setCursor(0,0);
    g_lcd.print("CbIPbE ...");
}

//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

void downEnter()
{
    g_lcd.clear();
    g_lcd.setCursor(0,1);
    g_lcd.print("Press ...");
    plcResetTime();
    if (readPlcInput( SENSOR_BOTTOM ) == LOW)
    {
        writePlcOutput( SOLENOID_DOWN, HIGH );
    }
}

void downRun()
{
    if (readPlcInput( SENSOR_BOTTOM ) == HIGH)
    {
        plcChangeState( STATE_UP );
    }
}

void downExit()
{
    writePlcOutput( SOLENOID_DOWN, LOW );
    delay(pressDelayMs);
}

