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

#include "p_checks.h"

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

void checkBeforeDownEnter()
{
}

void checkBeforeDownRun()
{
    if (plcStateTime() > 800)
    {
        if (plcInputRead( SENSOR_REMOVED ) == HIGH)
        {
            if (g_finalPress)
            {
                plcChangeState( STATE_DOWN_FINAL );
            }
            else
            {
                plcChangeState( STATE_DOWN_FIRST );
            }
        }
    }
    if (plcInputRead( SENSOR_REMOVED ) == LOW)
    {
        // According to logic, we should never fall here
        plcFault( ERROR_CODE_FAR_SENSOR );
    }
}

void checkBeforeDownExit()
{
}

//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

