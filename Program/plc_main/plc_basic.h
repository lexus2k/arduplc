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

#include <stdint.h>

typedef enum
{
    PLC_START_STATE       = 0x00,
    PLC_END_STATE         = 0x01,
    PLC_JMP               = 0x02,
    PLC_PAUSE             = 0x03,
    PLC_SET_OUT           = 0x07,
    PLC_JMP_ON_TIMEOUT    = 0x83,
    PLC_JMP_ON_INPUTS     = 0x84,
    PLC_JMP_STATE         = 0x86,
    PLC_STOP              = 0xFF,
} EPlcCommand;

typedef uint8_t  PlcProgram[512];

uint8_t plcCommandLen(uint8_t cmd);

bool plcStateChangeCommand(uint8_t cmd);

static inline uint8_t plcReadArg8(const uint8_t *pc) { return *pc; };

static inline uint16_t plcReadArg16(const uint8_t *pc) { return (uint16_t)pc[0] | ((uint16_t)pc[1] << 8); };

static inline void plcWriteArg8(uint8_t *pc, uint8_t argv) { *pc = argv; };

static inline void plcWriteArg16(uint8_t *pc, uint16_t argv)
{
    pc[0] = argv & 0x00FF;
    pc[1] = argv >> 8;
};

