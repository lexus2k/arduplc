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

#include "plc_outputs.h"

#include <Arduino.h>

const static uint8_t s_outputPins[] =
{
    7,
    6,
    5,
    4,
    3,
    2,
};

void writePlcOutput(uint8_t output, int level)
{
    digitalWrite(s_outputPins[output], level);
}

int plcOutputsCount()
{
    return sizeof(s_outputPins)/sizeof(s_outputPins[0]);
}

void initPlcOutputs()
{
    for (uint8_t i=0; i<sizeof(s_outputPins); i++)
    {
        pinMode(s_outputPins[i], OUTPUT);
        digitalWrite(s_outputPins[i], LOW);
    }
}

void plcDisableOutputs()
{
    for (uint8_t i=0; i<sizeof(s_outputPins); i++)
    {
        digitalWrite(s_outputPins[i], LOW);
    }
}
