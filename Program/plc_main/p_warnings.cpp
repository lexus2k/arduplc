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

#include "p_warnings.h"

#include "p_states.h"
#include "p_main_menu.h"

#include "plc_inputs.h"
#include "plc_outputs.h"
#include "plc_settings.h"
#include "plc_lcd.h"
#include "plc_buttons.h"
#include "plc_sme.h"

void warningDisconnectEnter()
{
    g_lcd.backlight();
    g_lcd.clear();
    g_lcd.setCursor(0, 0);
    g_lcd.print("OTCOE\x02""UHUTE");
    g_lcd.setCursor(0, 1);
    g_lcd.print("CTAHOK! WAIT");
}

void warningDisconnectRun()
{
    if (g_buttons.isShortPress())
    {
        plcChangeState(STATE_MAIN_MENU);
    }
}

void warningDisconnectExit()
{
    mainMenu.setSelection( MENU_TIMINGS );
    mainMenu.show();
}
