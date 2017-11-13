#include "plc_basic.h"

#include <stdint.h>

uint8_t plcCommandLen(uint8_t cmd)
{
    switch (cmd)
    {
        case PLC_END_STATE:
        case PLC_STOP:
            return 1;
        case PLC_SET_OUT:
            return 2;
        case PLC_START_STATE:
        case PLC_JMP:
        case PLC_JMP_STATE:
        case PLC_PAUSE:
            return 3;
        case PLC_JMP_ON_TIMEOUT:
        case PLC_JMP_ON_INPUTS:
            return 5;
        default:
            break;
    }
    return 0;
}

bool plcStateChangeCommand(uint8_t cmd)
{
    return (cmd & 0x80) != 0;
}
