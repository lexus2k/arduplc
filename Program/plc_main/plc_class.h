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


class PlcController
{
public:
    PlcController();
    void setup();

    void reset();
    void output(uint8_t n, bool level);
    bool input(uint8_t n);

private:
    static const uint8_t MAX_INPUTS  = 16;
    static const uint8_t MAX_OUTPUTS = 16;
    uint8_t m_inputs[MAX_INPUTS];
    uint8_t m_outputs[MAX_INPUTS];
    uint8_t m_inputsCount;
    uint8_t m_outputsCount;
};


