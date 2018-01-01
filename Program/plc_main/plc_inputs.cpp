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

#if LOW != 0
    #error "LOW is defined as non-zore, there could be issues"
#endif

/*
    Input pins: 
    10,
    11,
    12,
    13,
    14,
    15,
    16,
*/

static const uint8_t s_inputCount = 7;

static uint8_t    s_lpf[s_inputCount] = { 0 };
static uint8_t    s_lastValue[s_inputCount] = { 0 };
static volatile uint16_t s_pcint0Ts[s_inputCount] = {0};
static volatile uint8_t  s_pinb;
static volatile uint8_t  s_pinc;

int plcInputsCount()
{
    return s_inputCount;
}

int  plcInputsRefresh()
{
    for (uint8_t i=0; i<s_inputCount; i++)
    {
        plcInputRead( i );
    }
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
}

ISR(PCINT0_vect)
{
    uint8_t  pinb = s_pinb^PINB;
    uint16_t ts = millis();
    if (pinb & (1<<PINB2)) s_pcint0Ts[0] = ts;
    if (pinb & (1<<PINB3)) s_pcint0Ts[1] = ts;
    if (pinb & (1<<PINB4)) s_pcint0Ts[2] = ts;
    if (pinb & (1<<PINB5)) s_pcint0Ts[3] = ts;
    s_pinb ^= pinb;
}

ISR(PCINT1_vect)
{
    uint8_t  pinc = s_pinc^PINC;
    uint16_t ts = millis();
    if (pinc & (1<<PINC0)) s_pcint0Ts[4] = ts;
    if (pinc & (1<<PINC1)) s_pcint0Ts[5] = ts;
    if (pinc & (1<<PINC2)) s_pcint0Ts[6] = ts;
    s_pinc ^= pinc;
}

void plcInputsInit()
{
    DDRB &= ~( (1<<PINB2) | (1<<PINB3) | (1<<PINB4) | (1<<PINB5) );
    PORTB |= ( (1<<PINB2) | (1<<PINB3) | (1<<PINB4) | (1<<PINB5) );
    DDRC &= ~( (1<<PINC0) | (1<<PINC1) | (1<<PINC2) );
    PORTC |= ( (1<<PINC0) | (1<<PINC1) | (1<<PINC2) );
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
