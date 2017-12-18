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

#include "p_shake_left.h"

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

void shakeLeftEnter()
{
    if (readPlcInput( SENSOR_PULLED ) == LOW)
    {
        writePlcOutput( SOLENOID_COMMON, HIGH );
        writePlcOutput( SOLENOID_PULL_OUT, HIGH );
    }
}

void shakeLeftRun()
{
    if (readPlcInput( SENSOR_PULLED ) == HIGH)
    {
        g_shakes--;
        if (g_shakes)
        {
            plcChangeState( STATE_SHAKE_RIGHT );
        }
        else
        {
            plcChangeState( STATE_REMOVE );
        }
    }
}

void shakeLeftExit()
{
    writePlcOutput( SOLENOID_COMMON, LOW );
    writePlcOutput( SOLENOID_PULL_OUT, LOW );
    delay(loadDelayMs);
}

//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

void removeBriquetteEnter()
{
    g_lcd.clear();
    g_lcd.setCursor(0,1);
    g_lcd.print("6puKeTbI...");
    plcResetTime();
    if (readPlcInput( SENSOR_PULLED ) == LOW)
    {
        writePlcOutput( SOLENOID_COMMON, HIGH );
        writePlcOutput( SOLENOID_PULL_OUT, HIGH );
    }
}

void removeBriquetteRun()
{
    if (readPlcInput(SENSOR_PULLED) == HIGH)
    {
        plcChangeState( STATE_DOWN_CENTER );
    }
}

void removeBriquetteExit()
{
    writePlcOutput( SOLENOID_COMMON, LOW );
    writePlcOutput( SOLENOID_PULL_OUT, LOW );
}

//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
