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

#include "plc_inputs.h"

#include <Arduino.h>

static const uint8_t s_inputPins[] =
{
    10,
    11,
    12,
    13,
    14,
    15,
    16,
};

static const uint8_t s_inputCount = sizeof(s_inputPins)/sizeof(s_inputPins[0]);

uint8_t s_timestamp[s_inputCount] = { 0 };
uint8_t s_lpf[s_inputCount] = { 0 };
uint8_t s_lastValue[s_inputCount] = { 0 };

int plcInputsCount()
{
    return s_inputCount;
}

int plcInputRead(uint8_t input)
{
    /* Invert values, because input sensors use LOW as active. see Schematics */
    int value = LOW == digitalRead(s_inputPins[input]) ? HIGH: LOW;
    return value;
/*    s_timestamp[input] = millis();
    while ( s_lastValue[input] != value )
    {
        if (s_lpf[input])
        {
            uint8_t ts = millis();
            if (ts - s_timestamp[input] >= s_lpf[input])
            {
                s_lastValue[input] = value;
                break;
            }
            value = LOW == digitalRead(s_inputPins[input]) ? HIGH: LOW;
        }
        else
        {
            s_lastValue[input] = value;
            break;
        }
    }
    return value;*/
}

void plcInputsInit()
{
    for (uint8_t i=0; i<sizeof(s_inputPins); i++)
    {
        pinMode(s_inputPins[i], INPUT_PULLUP);
        s_timestamp[i] = millis();
        s_lpf[i] = 0;
        s_lastValue[i] = LOW;
    }
}

int plcInputLpf(uint8_t input, uint8_t ms)
{
    s_lpf[input] = ms;
}
