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


class PlcEngine
{
public:
    PlcEngine(uint8_t * program);

    void start();
    bool run(uint8_t inputs, uint8_t *outputs);

private:
    uint16_t     m_pc;
    uint8_t    * m_prog;
    uint16_t     m_exitAddress;
    uint16_t     m_newState;
    uint32_t     m_timestamp;

    uint8_t      readArg8();
    uint16_t     readArg16();
    uint16_t     findBlock(uint8_t cmd);
};
