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
// VERIFIED
#include "p_shake_left.h"

#include "p_states.h"
#include "p_sensors.h"
#include "p_solenoids.h"

#include "plc_inputs.h"
#include "plc_outputs.h"
#include "plc_settings.h"

#include <Arduino.h>

//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

void shakeLeftEnter()
{
    if (plcInputRead( SENSOR_PULLED ) == LOW)
    {
        writePlcOutput( SOLENOID_PULL_OUT, HIGH );
    }
    else
    {
        // According to logic, we should never fall here
        plcFault(1);
    }
}

void shakeLeftRun()
{
    if (plcInputRead( SENSOR_PULLED ) == HIGH)
    {
        /* This check to prevent problems with wrong input value */
        if (g_shakes > 0)
        {
            g_shakes--;
        }
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
    writePlcOutput( SOLENOID_PULL_OUT, LOW );
    delay(loadDelayMs);
}

//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

void removeBriquetteEnter()
{
    if (plcInputRead( SENSOR_PULLED ) == LOW)
    {
        writePlcOutput( SOLENOID_PULL_OUT, HIGH );
    }
    else
    {
        // According to logic, we should never fall here
        plcFault(1);
    }
}

void removeBriquetteRun()
{
    if (plcInputRead(SENSOR_PULLED) == HIGH)
    {
        if (plcStateTime()<500)
        {
            // Too fast, cannot be!
            plcFault(2);
        }
        else
        {
            plcChangeState( STATE_DOWN_CENTER );
        }
    }
}

void removeBriquetteExit()
{
    writePlcOutput( SOLENOID_PULL_OUT, LOW );
}

//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
