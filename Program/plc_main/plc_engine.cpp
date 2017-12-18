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

#include "plc_engine.h"
#include "plc_basic.h"

#if defined(ARDUINO) || defined(__AVR_ATmega328P__)
#include <Arduino.h>
#endif

PlcEngine::PlcEngine(uint8_t * program)
{
    m_prog = program;
    start();
}

void PlcEngine::start()
{
    m_pc = 0;
}


bool PlcEngine::run(uint8_t inputs, uint8_t *outputs)
{
    bool iterationDone = false;
    while (!iterationDone)
    {
        uint8_t cmd = readArg8();
        m_pc++;
        switch ( cmd )
        {
            case PLC_JMP:
                /* Unconditional jump */
                m_pc = readArg16();
                /* We performed all checks in the cycle. Now we can exit */
                iterationDone = true;
                break;
    
            case PLC_JMP_ON_INPUTS:
                {
                    m_newState = readArg16();
                    uint8_t mask = readArg8();
                    uint8_t value = readArg8();
                    if ( mask & inputs == value )
                    {
                        m_pc = m_exitAddress;
                    }
                }
                break;
    
            case PLC_JMP_ON_TIMEOUT:
                {
                    m_newState = readArg16();
                    uint32_t timeout = readArg16();
                    if ((millis() - m_timestamp) >= timeout)
                    {
                        m_pc = m_exitAddress;
                    }
                }
                break;
    
            case PLC_JMP_STATE:
                m_timestamp = millis();
                m_newState = readArg16();
                m_pc = m_exitAddress;
                break;
    
           case PLC_SET_OUT:
                {
                    uint8_t param = readArg8();
                    uint8_t index = (param & 0x7F);
                    if (param & 0x80 != 0)
                    {
                        *outputs |= (1 << index);
                    }
                    else
                    {
                        *outputs &= ~(1 << index);
                    }
                }
                break;

           case PLC_PAUSE:
                {
                    uint32_t timeout = readArg16();
                    delay( timeout );
                }
                break;
    
           case PLC_START_STATE:
                m_exitAddress = readArg16();
                break;
    
            case PLC_END_STATE:
                /* Do jump to next state */
                m_pc = m_newState;
                /* We're switching to new state, exit and process other events */
                iterationDone = true;
                break;
            case PLC_STOP:
                return false;
            default:
                /* Error, unknown command */
                return false;
        }
    }
    return true;
}


uint8_t PlcEngine::readArg8()
{
    uint8_t argv = plcReadArg8(&m_prog[m_pc]);
    m_pc++;
    return argv;
}

uint16_t PlcEngine::readArg16()
{
    uint16_t argv = plcReadArg16(&m_prog[m_pc]);
    m_pc+=2;
    return argv;
}

uint16_t PlcEngine::findBlock(uint8_t cmd)
{
    uint16_t temp = m_pc;
    while ( m_prog[temp] != cmd )
    {
        temp += plcCommandLen( m_prog[temp] );
    }
}

