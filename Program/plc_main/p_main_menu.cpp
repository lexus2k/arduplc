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

#include "p_main_menu.h"

#include "p_states.h"
#include "plc_settings.h"

#include "plc_inputs.h"
#include "plc_outputs.h"
#include "plc_lcd.h"
#include "plc_buttons.h"
#include "plc_sme.h"


static MenuItem menuItems[] =
{
    { MENU_START,       "CTAPT" },
    { MENU_STATISTICS,  "CTATUCTUKA" },
    { MENU_NONE,        nullptr },
    { MENU_AUTOMODE,    "ABTOMAT", MENU_ITEM_BOOL, &automaticMode },
    { MENU_PRE_PRESS,   "\x01O\x02\x01PECCOB.", MENU_ITEM_BOOL, &prePressingMode },
    { MENU_LOAD_CYCLES, "\x01POXO\x02""bl", MENU_ITEM_UINT8, &shakeCount },
    { MENU_PRESS_TIME,  "\x02""ABUTb", MENU_ITEM_TIME16, &pressDelayMs },
    { MENU_MOVE_RIGHT_TIME,  "B\x01PABO",   MENU_ITEM_TIME16, &shakeMoveRightMs },
    { MENU_SHAKER_TIME, "3A\xA2Py3KA", MENU_ITEM_TIME16, &loadDelayMs },
    { MENU_SAVE_SETTINGS, "COXPAHUTb" },
    { MENU_RESET,       "3A\xA2Py3UTb" },
    { MENU_NONE,        nullptr },
    { MENU_MANUAL,      "MANUAL" },
    { MENU_TIMINGS,     "!\x01O\x02""COE\x02.", MENU_ITEM_BOOL,   &enableTimings },
    { MENU_DIAG,        "\x02UA\xA2HOCTUKA"},
};

TinyMenu mainMenu(menuItems, sizeof(menuItems) / sizeof(menuItems[0]));

static void registerArrow()
{
    uint8_t arrow[8] = {
        B00001000,
        B00001100,
        B00001110,
        B00001111,
        B00001110,
        B00001100,
        B00001000,
        B00000000,
    };
    g_lcd.createChar(0, arrow);
}

static void registerP()
{
    uint8_t p_letter[8] = {
        B00011111,
        B00010001,
        B00010001,
        B00010001,
        B00010001,
        B00010001,
        B00010001,
        B00000000,
    };
    g_lcd.createChar(1, p_letter);
}

static void registerD()
{
    uint8_t d_letter[8] = {
        B00000111,
        B00000101,
        B00000101,
        B00001001,
        B00001001,
        B00001001,
        B00011111,
        B00010001,
    };
    g_lcd.createChar(2, d_letter);
}

void mainMenuEnter()
{
    registerArrow();
    registerP();
    registerD();
    g_lcd.backlight();
    mainMenu.show();
}

void mainMenuRun()
{
    if (g_buttons.isShortPress(PLC_BUTTON_UP))
    {
        mainMenu.up();
        mainMenu.show();
    }
    if (g_buttons.isShortPress(PLC_BUTTON_DOWN))
    {
        mainMenu.down();
        mainMenu.show();
    }
    if (g_buttons.isLongHold(PLC_BUTTON_SELECT, millis(), 2000))
    {
        switch (mainMenu.selection())
        {
            case MENU_START:
                plcChangeState(STATE_INIT);
                break;
            case MENU_MANUAL:
                manualModeDiag = 1;
                plcChangeState(STATE_PLC_DIAG);
                break;
            case MENU_DIAG:
                manualModeDiag = 0;
                plcChangeState(STATE_PLC_DIAG);
                break;
            case MENU_SAVE_SETTINGS:
                saveSettings();
                tone(8, 1000); delay(300);
                tone(8, 500); delay(200);
                tone(8, 200); delay(100);
                noTone(8);
                break;
            case MENU_TIMINGS:
                enableTimings = enableTimings == 0 ? 1: 0;
                if (0 == enableTimings)
                {
                    plcChangeState(STATE_WARNING_DISCONNECT);
                }
                else
                {
                    mainMenu.show();
                }
                break;
            case MENU_RESET:
                loadSettings();
                tone(8, 1000); delay(300);
                tone(8, 500); delay(200);
                tone(8, 200); delay(100);
                noTone(8);
                mainMenu.show();
                break;
            default:
                break;
        }
    }
    if (g_buttons.isShortPress(PLC_BUTTON_SELECT))
    {
        switch (mainMenu.selection())
        {
            case MENU_AUTOMODE:
                automaticMode = automaticMode == 0 ? 1: 0;
                mainMenu.show();
                break;
            case MENU_PRE_PRESS:
                prePressingMode = prePressingMode == 0 ? 1: 0;
                mainMenu.show();
                break;
            case MENU_LOAD_CYCLES:
                shakeCount++; if (shakeCount>5) shakeCount=1;
                mainMenu.show();
                break;
            case MENU_PRESS_TIME:
                pressDelayMs+=1000; if (pressDelayMs>10000) pressDelayMs = 1000;
                mainMenu.show();
                break;
            case MENU_MOVE_RIGHT_TIME:
                shakeMoveRightMs+=100; if (shakeMoveRightMs>900) shakeMoveRightMs = 100;
                mainMenu.show();
                break;
            case MENU_SHAKER_TIME:
                loadDelayMs+=50; if (loadDelayMs>600) loadDelayMs = 0;
                mainMenu.show();
                break;
            default:
                break;
        }
    }
    plcInputsRefresh();
}

void mainMenuExit()
{
}
