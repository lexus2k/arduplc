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

#pragma once

#include "tiny_menu.h"

enum
{
    MENU_START,
    MENU_STATISTICS,
    MENU_AUTOMODE,
    MENU_PRE_PRESS,
    MENU_LOAD_CYCLES,
    MENU_PRESS_TIME,
    MENU_MOVE_RIGHT_TIME,
    MENU_SHAKER_TIME,
    MENU_UP_TIME,
    MENU_TIMINGS,
    MENU_SAVE_SETTINGS,
    MENU_DIAG,
    MENU_RESET,
    MENU_MANUAL,
    MENU_NONE,
};

extern TinyMenu mainMenu;


void mainMenuEnter();
void mainMenuRun();
void mainMenuExit();

