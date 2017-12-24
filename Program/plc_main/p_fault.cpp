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

#include "p_fault.h"

#include "p_states.h"
#include "p_sensors.h"
#include "p_solenoids.h"

#include "plc_inputs.h"
#include "plc_outputs.h"
#include "plc_buttons.h"
#include "plc_lcd.h"

#include <Arduino.h>

void faultEnter()
{
    initPlcOutputs();
    g_lcd.clear();
    delay(10);
    g_lcd.backlight();
    delay(10);
    g_lcd.setCursor(0,0);
    g_lcd.print("## ERROR ##");

    SFaultInfo info = plcGetFaultInfo();
    g_lcd.setCursor(0,1);
    if (info.state != nullptr)
    {
        g_lcd.print(info.state->name);
        g_lcd.print(":");
    }
    g_lcd.print(info.data);

    tone(8, 400, 500);
    delay(1000);
    tone(8, 400, 500);
    delay(1000);
    tone(8, 400);
    delay(500);
    noTone(8);
}

void faultRun()
{
    if (g_buttons.isShortPress())
    {
        plcChangeState(STATE_MAIN_MENU);
    }
}

void faultExit()
{
}

