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
#include <avr/io.h>
#include <avr/interrupt.h>

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

static uint8_t    s_lpf[s_inputCount] = { 0 };
static uint8_t    s_lastValue[s_inputCount] = { 0 };
static volatile uint16_t s_pcint0Ts[s_inputCount] = {0};
static volatile uint8_t  s_pinb;
static volatile uint8_t  s_pinc;

int plcInputsCount()
{
    return s_inputCount;
}

int plcInputRead(uint8_t input)
{
    uint8_t value = s_lastValue[input];
    uint8_t oldSREG;
    uint16_t ts = millis();
    oldSREG = SREG;
    cli();
    if (ts - s_pcint0Ts[input] >= s_lpf[input])
    {
        /* Invert values, because input sensors use LOW as active. see Schematics */
        if (input<4)
        {
            value = s_pinb & (1<<(input+2)) ? LOW: HIGH;
        }
        else
        {
            value = s_pinc & (1<<(input-4)) ? LOW: HIGH;
        }
    }
    SREG = oldSREG;
    s_lastValue[input] = value;
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

ISR(PCINT0_vect)
{
    uint8_t  pinb = s_pinb^PINB;
    uint16_t ts = millis();
    if (pinb & 0x04) s_pcint0Ts[0] = ts;
    if (pinb & 0x08) s_pcint0Ts[1] = ts;
    if (pinb & 0x10) s_pcint0Ts[2] = ts;
    if (pinb & 0x20) s_pcint0Ts[3] = ts;
    s_pinb ^= pinb;
}

ISR(PCINT1_vect)
{
    uint8_t  pinc = s_pinc^PINB;
    uint16_t ts = millis();
    if (pinc & 0x01) s_pcint0Ts[4] = ts;
    if (pinc & 0x02) s_pcint0Ts[5] = ts;
    if (pinc & 0x04) s_pcint0Ts[6] = ts;
    s_pinc ^= pinc;
}

void plcInputsInit()
{
    for (uint8_t i=0; i<sizeof(s_inputPins); i++)
    {
        pinMode(s_inputPins[i], INPUT_PULLUP);
        s_lpf[i] = 0;
        s_lastValue[i] = LOW;
    }
    PCMSK0 |= (1<<PCINT2);   // 10
    PCMSK0 |= (1<<PCINT3);   // 11
    PCMSK0 |= (1<<PCINT4);   // 12
    PCMSK0 |= (1<<PCINT5);   // 13
    PCMSK1 |= (1<<PCINT8);   // 14
    PCMSK1 |= (1<<PCINT9);   // 15
    PCMSK1 |= (1<<PCINT10);  // 16
    PCICR  |= (1<<PCIE0);
    PCICR  |= (1<<PCIE1);
    s_pinb = PINB;
    s_pinc = PINC;
    sei();
}

int plcInputLpf(uint8_t input, uint8_t ms)
{
    s_lpf[input] = ms;
}
