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

#include "plc_engine.h"
#include "plc_inputs.h"
#include "plc_outputs.h"
#include "plc_sme.h"
#include "p_states.h"
#include "plc_lcd.h"
#include "plc_buttons.h"

#include <Arduino.h>
#include <Wire.h>

void setup()
{
    plcInitSme( programStates, programStatesCount(), STATE_POWER_ON );
}

void loop()
{
    g_buttons.update();
    plcRunSme();
    if (plcGetState() > STATE_PASSIVE)
    {
        if (g_buttons.isShortPress())
        {
            plcForceChangeState( STATE_MAIN_MENU );
            plcDisableOutputs();
            tone(8, 200); delay(300);
            tone(8, 500); delay(200);
            tone(8, 1000); delay(100);
            noTone(8);
        }
    }
}
