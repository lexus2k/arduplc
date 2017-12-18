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

#include "plc_class.h"

#include <Arduino.h>

PlcController::PlcController()
{
    m_inputsCount = 0;
    m_outputsCount = 0;
}

void PlcController::setup()
{
    for (uint8_t i=0; i<m_outputsCount; i++)
    {
        pinMode(m_outputs[i], OUTPUT);
        digitalWrite(m_outputs[i], LOW);
    }
    for (uint8_t i=0; i<m_inputsCount; i++)
    {
        pinMode(m_inputs[i], INPUT_PULLUP);
    }
}

void PlcController::reset()
{
}

void PlcController::output(uint8_t n, bool level)
{
    if (n <= m_outputsCount)
    {
        digitalWrite(m_outputs[n], level ? HIGH: LOW);
    }
}

bool PlcController::input(uint8_t n)
{
    if (n <= m_inputsCount)
    {
        /* Invert values, because input sensors use LOW as active. see Schematics */
        if (LOW == digitalRead(m_inputs[n])) return true;
    }
    return false;
}


