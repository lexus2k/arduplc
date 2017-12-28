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

#include "p_power_on.h"

#include "p_states.h"
#include "p_sensors.h"

#include "plc_inputs.h"
#include "plc_outputs.h"
#include "plc_settings.h"
#include "plc_lcd.h"
#include "plc_buttons.h"
#include "plc_sme.h"


/**
 * Use 15 milliseconds for LPF before taking decision about changed input.
 * On actual machine, there can be noise on sensor lines, which causes fast
 * controller to make wrong decisions. In original schematics only relays were
 * used to control machine, and since relay are inert (switching on delay is about
 * 15ms for DRI424024LTD), the scheme doesn't sense noise 133 Hz and higher 
 * (1000ms/(15ms/2)). But for uC this is not true, so, implement LPF in software
 * to reduce false-positive decisions.
 */
static const uint8_t PLC_INPUT_LPF_TIMEOUT_MS = 15;

void powerOnEnter()
{
    pinMode(8, OUTPUT); // sound

    initPlcOutputs();
    plcInputsInit();
    // Enable LPF for 20 milliseconds for false-positive check
    plcInputLpf(SENSOR_REMOVED,           PLC_INPUT_LPF_TIMEOUT_MS);
    plcInputLpf(SENSOR_PULLED,            PLC_INPUT_LPF_TIMEOUT_MS);
    plcInputLpf(SENSOR_TOP,               PLC_INPUT_LPF_TIMEOUT_MS);
    plcInputLpf(SENSOR_MIDDLE,            PLC_INPUT_LPF_TIMEOUT_MS);
    plcInputLpf(SENSOR_BOTTOM,            PLC_INPUT_LPF_TIMEOUT_MS);
    plcInputLpf(SENSOR_BOTTOM_PREPRESS,   PLC_INPUT_LPF_TIMEOUT_MS);

    loadSettings();
    g_buttons.init();
    g_lcd.init();
    g_lcd.backlight();
    g_lcd.clear();
    g_lcd.setCursor(0, 0);
    g_lcd.print("Powering on...");
}

void powerOnRun()
{
    plcChangeState(STATE_MAIN_MENU);
}

void powerOnExit()
{
}
