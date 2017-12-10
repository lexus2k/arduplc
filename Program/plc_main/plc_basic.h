
#pragma once

#include <stdint.h>

typedef enum
{
    PLC_START_STATE       = 0x00,
    PLC_END_STATE         = 0x01,
    PLC_JMP               = 0x02,
    PLC_PAUSE             = 0x03,
    PLC_SET_OUT           = 0x07,
    PLC_JMP_ON_TIMEOUT    = 0x83,
    PLC_JMP_ON_INPUTS     = 0x84,
    PLC_JMP_STATE         = 0x86,
    PLC_STOP              = 0xFF,
} EPlcCommand;

typedef uint8_t  PlcProgram[512];

uint8_t plcCommandLen(uint8_t cmd);

bool plcStateChangeCommand(uint8_t cmd);

static inline uint8_t plcReadArg8(const uint8_t *pc) { return *pc; };

static inline uint16_t plcReadArg16(const uint8_t *pc) { return (uint16_t)pc[0] | ((uint16_t)pc[1] << 8); };

static inline void plcWriteArg8(uint8_t *pc, uint8_t argv) { *pc = argv; };

static inline void plcWriteArg16(uint8_t *pc, uint16_t argv)
{
    pc[0] = argv & 0x00FF;
    pc[1] = argv >> 8;
};

