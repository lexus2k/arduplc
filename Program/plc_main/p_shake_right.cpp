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

#include "p_shake_right.h"

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

void shakeRightEnter()
{
    if (readPlcInput( SENSOR_REMOVED ) == LOW)
    {
        writePlcOutput( SOLENOID_COMMON, HIGH );
        writePlcOutput( SOLENOID_REMOVE, HIGH );
    }
}

void shakeRightRun()
{
    if (plcStateTime() >= shakeDelayMs)
    {
        plcChangeState( STATE_SHAKE_LEFT );
    }
    if (readPlcInput( SENSOR_REMOVED ) == HIGH)
    {
        plcFault();
    }
}

void shakeRightExit()
{
    writePlcOutput( SOLENOID_COMMON, LOW );
    writePlcOutput( SOLENOID_REMOVE, LOW );
}

//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

void removeEnter()
{
    if (readPlcInput( SENSOR_REMOVED ) == LOW)
    {
        writePlcOutput( SOLENOID_COMMON, HIGH );
        writePlcOutput( SOLENOID_REMOVE, HIGH );
    }
}

void removeRun()
{
    if (readPlcInput( SENSOR_REMOVED ) == HIGH)
    {
        if (g_finalPress)
        {
            plcChangeState( STATE_DOWN );
        }
        else
        {
            plcChangeState( STATE_DOWN_TEMP );
        }
    }
}

void removeExit()
{
    writePlcOutput( SOLENOID_COMMON, LOW );
    writePlcOutput( SOLENOID_REMOVE, LOW );
}

