
#pragma once

#include "plc_basic.h"

#include <stdint.h>

#define PLC_MAX_STATES    32
#define PLC_INVALID_STATE 0xFFFF

typedef struct
{
    char     name[17];
    uint16_t enterAddress;
    uint16_t eventsAddress;
    uint16_t exitAddress;
} SStateInfo;

class PlcCompiler
{
public:
    PlcCompiler(uint8_t * binaryProg, uint16_t maxSize);
    bool compile(const char * source);

    bool compileLine(const char * line);
    bool finalize();

    uint16_t    getErrorLine() { return m_line; };
    uint16_t    getBinarySize() { return m_pc; };
    
private:
    SStateInfo  m_states[PLC_MAX_STATES];
    uint16_t    m_statesCount;
    uint16_t    m_currentState;
    uint16_t    m_pc;
    uint8_t    *m_prog;
    uint16_t    m_maxSize;
    uint16_t     m_line;

    bool        addArg8(uint8_t argv);
    bool        addArg16(uint16_t argv);
    uint16_t    registerState(const char *plc_str, uint8_t len);
    uint16_t    getStateByName(const char *plc_str, uint8_t len);
    bool        addState(const char *plc_str, uint8_t len);
    bool        finalizeCurrentState();

    bool        parsePauseCmd(const char *args);
    bool        parseStateCmd(const char *args);
    bool        parseExitCmd(const char *args);
    bool        parseEventsCmd(const char *args);
    bool        parseSetCmd(const char *args);
    bool        parseOnCmd(const char *args);
    bool        parseGotoCmd(const char *args);
    bool        parseTimeoutCmd(const char *args);
};

