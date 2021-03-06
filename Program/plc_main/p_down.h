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


/* Move do mid point down */
void downCenterEnter();
void downCenterRun();
void downCenterExit();

/* Move to bottom sensor */
void downFinalEnter();
void downFinalRun();
void downFinalExit();

/* Move to temp sensor (pre-pressing) */
void downFirstEnter();
void downFirstRun();
void downFirstExit();

