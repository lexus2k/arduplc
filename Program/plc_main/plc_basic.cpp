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

#include "plc_basic.h"

#include <stdint.h>

uint8_t plcCommandLen(uint8_t cmd)
{
    switch (cmd)
    {
        case PLC_END_STATE:
        case PLC_STOP:
            return 1;
        case PLC_SET_OUT:
            return 2;
        case PLC_START_STATE:
        case PLC_JMP:
        case PLC_JMP_STATE:
        case PLC_PAUSE:
            return 3;
        case PLC_JMP_ON_TIMEOUT:
        case PLC_JMP_ON_INPUTS:
            return 5;
        default:
            break;
    }
    return 0;
}

bool plcStateChangeCommand(uint8_t cmd)
{
    return (cmd & 0x80) != 0;
}
