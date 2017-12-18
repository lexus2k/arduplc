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


#include "plc_compiler.h"

#include "plc_engine.h"

#include <stdint.h>
#include <ctype.h>
#include <string.h>

//#include <stdio.h>

PlcCompiler::PlcCompiler(uint8_t * binaryProg, uint16_t maxSize)
{
    m_prog = binaryProg;
    m_maxSize = maxSize;
    for (uint16_t i=0; i<PLC_MAX_STATES; i++)
    {
        memset(&m_states[i], 0, sizeof(SStateInfo));
    }
    m_currentState = PLC_INVALID_STATE;
    m_statesCount = 0;
    m_pc = 0;
}


static uint8_t findWordLen(const char * ptr)
{
    uint8_t i = 0;
    while (isalnum(ptr[i]) || (ptr[i] == '_') || (ptr[i] == '!'))
    {                                                          
        i++;
    }
    return i;
}

static inline uint8_t findArgStart(const char * ptr)
{
    uint8_t i=0;
    while (ptr[i] == ' ')
    {
        i++;
    }
    if (!isalnum(ptr[i]) && (ptr[i] != '_') && (ptr[i] != '!')) return 0;
    return i;
}

static inline uint8_t nextWord(const char **ptr, const char *line)
{
    uint8_t start = findArgStart( line );
    if (ptr) *ptr = line + start;
    return findWordLen( line + start );
}

static int plc_strcmp(const char * plc_str, uint8_t len, const char * base)
{
    if (len != strlen(base)) return 1;
    return memcmp(plc_str, base, len);
}

static int plc_atoi(const char * plc_str, uint8_t len)
{
    int i = 0;
    while ( isdigit(*plc_str) )
    {
        i=i*10 + (*plc_str - '0');
        plc_str++;
    }
    return i;
}

static const char * plc_next_line(const char *p)
{
    bool found = false;
    for(;;)
    {
        if (*p == '\0') return NULL;
        if (found) break;
        if (*p == '\n') found = true;
        p++;
    }
    return p;
}

bool PlcCompiler::compile(const char * source)
{
    m_currentState = PLC_INVALID_STATE;
    m_statesCount = 0;
    m_pc = 0;
    m_line = 1;
    const char * p = source;
    while (p != NULL)
    {
        if (!compileLine(p))
        {
            return false;
        }
        p = plc_next_line(p);
        m_line++;
    }
    return finalize();
}

bool PlcCompiler::compileLine(const char * line)
{
    char ch = line[0];
    switch (ch)
    {
        case '\n':
        case '\r':
        case '#':
            return true;
    }
    const char * param;
    uint8_t paramLen = nextWord( &param, line );
    if ( paramLen == 0 )
    {
        return false;
    }
    bool result = false;
    if (!plc_strcmp( param, paramLen, "STATE" )) result = parseStateCmd( param + paramLen );
    else if (!plc_strcmp( param, paramLen, "EVENTS" )) result = parseEventsCmd( param + paramLen );
    else if (!plc_strcmp( param, paramLen, "EXIT" )) result = parseExitCmd( param + paramLen );
    else if (!plc_strcmp( param, paramLen, "SET" )) result = parseSetCmd( param + paramLen );
    else if (!plc_strcmp( param, paramLen, "ON" )) result = parseOnCmd( param + paramLen );
    else if (!plc_strcmp( param, paramLen, "GOTO" )) result = parseGotoCmd( param + paramLen );
    else if (!plc_strcmp( param, paramLen, "TIMEOUT" )) result = parseTimeoutCmd( param + paramLen );
    else if (!plc_strcmp( param, paramLen, "PAUSE" )) result = parsePauseCmd( param + paramLen );
    return result;
}

bool PlcCompiler::finalize()
{
    if (!finalizeCurrentState()) return false;
    uint16_t pc = 0;
    uint16_t currentState = 0;
    /* At this time, all states have well-known addresses */
    while ( pc < m_pc)
    {
        uint8_t cmd = plcReadArg8( &m_prog[pc] );
        if ( plcStateChangeCommand( cmd ) )
        {
            /* Replace state index with real state address */
            uint16_t stateAddress = plcReadArg16( &m_prog[pc+1] );
            stateAddress = m_states[stateAddress].enterAddress;
            plcWriteArg16( &m_prog[pc+1], stateAddress );
        }
        else if ( cmd == PLC_START_STATE )
        {
            /* Replace exit addresses with real ones */
            plcWriteArg16( &m_prog[pc+1], m_states[currentState].exitAddress );
        }
        else if ( cmd == PLC_END_STATE ) currentState++;
        pc += plcCommandLen( cmd );
    }
    return true;
}

bool PlcCompiler::addArg8(uint8_t argv)
{
    if (m_pc == m_maxSize) return false;
    m_prog[m_pc++] = argv;
    return true;
}

bool PlcCompiler::addArg16(uint16_t argv)
{
    addArg8(argv & 0x00FF);
    return addArg8( argv >> 8 );
}

uint16_t PlcCompiler::registerState(const char *plc_str, uint8_t len)
{
    if ((len > 16) || (len == 0))
    {
        return PLC_INVALID_STATE;
    }
    if ( m_statesCount >= PLC_MAX_STATES )
    {
        return PLC_INVALID_STATE;
    }
    memcpy((void *)m_states[m_statesCount].name, plc_str, len);
    m_states[m_statesCount].name[len] = '\0';
    m_states[m_statesCount].enterAddress  = 0x0000;
    m_states[m_statesCount].eventsAddress = 0x0000;
    m_states[m_statesCount].exitAddress   = 0x0000;
    m_statesCount++;
    return m_statesCount - 1;
}

uint16_t PlcCompiler::getStateByName(const char *plc_str, uint8_t len)
{
    for (uint16_t i=0; i < m_statesCount; i++)
    {
        if (!plc_strcmp(plc_str, len, m_states[i].name))
        {
            return i;
        }
    }
    return registerState(plc_str, len);
}

bool PlcCompiler::addState(const char *plc_str, uint8_t len)
{
    m_currentState = getStateByName(plc_str, len);
    return (m_currentState != PLC_INVALID_STATE);
}

bool PlcCompiler::finalizeCurrentState()
{
    if (m_currentState != PLC_INVALID_STATE)
    {
        // Check exit section, it can be empty
        if (!m_states[m_currentState].exitAddress)
        {
            if (!parseExitCmd( nullptr )) return false;
        }
        if (!addArg8( PLC_END_STATE )) return false;
    }
    return true;
}

bool PlcCompiler::parseStateCmd(const char *args)
{
    if (!finalizeCurrentState()) return false;
    uint8_t nameLen = nextWord(&args, &args[0]);
    if (!addState( args, nameLen )) return false;
    m_states[m_currentState].enterAddress = m_pc;
    addArg8( PLC_START_STATE );
    /* We do not know exit address yet, write 0x0 */
    addArg16( 0x00 );
    return true;
}

bool PlcCompiler::parseEventsCmd(const char *args)
{
    m_states[m_currentState].eventsAddress = m_pc;
    return true;
}

bool PlcCompiler::parseExitCmd(const char *args)
{
    addArg8( PLC_JMP );
    bool result = addArg16( m_states[m_currentState].eventsAddress );
    m_states[m_currentState].exitAddress = m_pc;
    return result;
}

bool PlcCompiler::parseSetCmd(const char *args)
{
    int len = 0;
    addArg8( PLC_SET_OUT );
    len = nextWord( &args, &args[len] );
    if ( !len ) return false;
    uint8_t output = plc_atoi( args, len ) - 1;
    len = nextWord( &args, &args[len] );
    if ( !len ) return false;
    if ( !plc_strcmp( args, len, "ON" ))
    {
        output |= 0x80;
    }
    else if ( !plc_strcmp( args, len, "OFF" ))
    {
        output &= 0x7F;
    }
    else
    {
        return false;
    }
    return addArg8( output );
}

bool PlcCompiler::parseOnCmd(const char *args)
{
    uint16_t len = 0;
    uint8_t  mask = 0x00;
    uint8_t  val = 0x00;
    len = nextWord( &args, &args[len] );
    while ( len >=2 )
    {
        uint8_t v;
        uint8_t m;
        if ( *args == '_' ) v=1;
        else if ( *args == '!' ) v=0;
        else return false;
        m = plc_atoi( args + 1, len - 1 );
        if (m > 8) return false;
        mask |= (1<<(m-1));
        val |= (v<<(m-1));
        if (args[len] != '&') break;
        args += len + 1;
        len = findWordLen( args );
    }
    if (!mask) return false;
    len = nextWord( &args, &args[len] );
    if (!len) return false;
    uint16_t state = getStateByName( args, len );
    if ( state == PLC_INVALID_STATE ) return false;
    addArg8( PLC_JMP_ON_INPUTS );
    /* We do not know state address, so, just put state index for now */
    addArg16( state );
    addArg8( mask );
    return addArg8( val );
}

bool PlcCompiler::parseGotoCmd(const char *args)
{
    uint16_t len = 0;
    len = nextWord( &args, &args[len] );
    if (!len) return false;
    uint16_t state = getStateByName( args, len );
    if ( state == PLC_INVALID_STATE ) return false;
    addArg8( PLC_JMP_STATE );
    /* We do not know state address, so, just put state index for now */
    return addArg16( state );
}

bool PlcCompiler::parseTimeoutCmd(const char *args)
{
    uint16_t len = 0;
    len = nextWord( &args, &args[len] );
    if (!len) return false;
    uint16_t timeout = plc_atoi(args, len);
    len = nextWord( &args, &args[len] );
    if (!len) return false;
    uint16_t state = getStateByName( args, len );
    if ( state == PLC_INVALID_STATE ) return false;
    addArg8( PLC_JMP_ON_TIMEOUT );
    /* We do not know state address, so, just put state index for now */
    addArg16( state );
    return addArg16( timeout );
}

bool PlcCompiler::parsePauseCmd(const char *args)
{
    uint16_t len = 0;
    len = nextWord( &args, &args[len] );
    if (!len) return false;
    uint16_t timeout = plc_atoi(args, len);
    addArg8( PLC_PAUSE );
    return addArg16( timeout );
}