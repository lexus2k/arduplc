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
#include "p_errors.h"
#include "p_sensors.h"
#include "p_solenoids.h"

#include "plc_inputs.h"
#include "plc_outputs.h"
#include "plc_settings.h"

#include <Arduino.h>

//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

void downFirstEnter()
{
    if (plcInputRead( SENSOR_BOTTOM_PREPRESS ) == LOW)
    {
        writePlcOutput( SOLENOID_DOWN, HIGH );
    }
    else
    {
        // According to logic, we should never fall here
        plcFault( ERROR_CODE_BOTTOM_PREPRESS_SENSOR );
    }
}

void downFirstRun()
{
    if (plcInputRead( SENSOR_BOTTOM_PREPRESS ) == HIGH)
    {
        plcChangeState( STATE_UP_MIDDLE );
    }
    if (plcInputRead( SENSOR_BOTTOM ) == HIGH)
    {
        // Either false reaction or prepress sensor doesn't work
        plcFault( ERROR_CODE_BOTTOM_SENSOR_F );
    }
}

void downFirstExit()
{
    writePlcOutput( SOLENOID_DOWN, LOW );
}


//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////


void downCenterEnter()
{
    if (plcInputRead( SENSOR_MIDDLE ) == LOW)
    {
        writePlcOutput( SOLENOID_DOWN, HIGH );
    }
    else
    {
        // According to logic, we should never fall here
        plcFault( ERROR_CODE_CENTER_SENSOR );
    }
}

void downCenterRun()
{
    if (plcInputRead( SENSOR_MIDDLE ) == HIGH)
    {
        plcChangeState( STATE_SHAKE_RIGHT );
        g_shakes = shakeCount;
        if (prePressingMode)
        {
            g_finalPress = false;
        }
        else
        {
            g_finalPress = true;
        }
    }
    if (prePressingMode && (plcInputRead( SENSOR_BOTTOM_PREPRESS ) == HIGH))
    {
        plcFault( ERROR_CODE_BOTTOM_PREPRESS_SENSOR_F );
    }
    if (plcInputRead( SENSOR_BOTTOM ) == HIGH)
    {
        plcFault( ERROR_CODE_BOTTOM_SENSOR_F );
    }
}

void downCenterExit()
{
    writePlcOutput( SOLENOID_DOWN, LOW );
}

//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

void downFinalEnter()
{
    if (plcInputRead( SENSOR_BOTTOM ) == LOW)
    {
        writePlcOutput( SOLENOID_DOWN, HIGH );
    }
    else
    {
        // According to logic, we should never fall here
        plcFault( ERROR_CODE_BOTTOM_SENSOR );
    }
}

void downFinalRun()
{
    if (plcInputRead( SENSOR_BOTTOM ) == HIGH)
    {
        plcChangeState( STATE_UP );
    }
}

void downFinalExit()
{
    writePlcOutput( SOLENOID_DOWN, LOW );
    delay(pressDelayMs);
}

