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

#include "p_stats.h"

#include "p_states.h"
#include "p_main_menu.h"

#include "plc_version.h"
#include "plc_settings.h"
#include "plc_lcd.h"
#include "plc_buttons.h"
#include "plc_sme.h"

void statsEnter()
{
    g_lcd.backlight();
    g_lcd.clear();
    g_lcd.setCursor(0, 0);
    g_lcd.print("BEP: ");
    g_lcd.print(PLC_VERSION_MAJOR);
    g_lcd.print(".");
    g_lcd.print(PLC_VERSION_MINOR);
    g_lcd.print(".");
    g_lcd.print(PLC_VERSION_PATCH);
    g_lcd.setCursor(0, 1);
    g_lcd.print("3A\x01yCKU: ");
    g_lcd.print(g_stats.cycles);
}

void statsRun()
{
    if (g_buttons.isShortPress())
    {
        plcChangeState(STATE_MAIN_MENU);
    }
}

void statsExit()
{
}
