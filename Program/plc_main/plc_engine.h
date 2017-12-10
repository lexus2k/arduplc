
#pragma once

#include <stdint.h>


class PlcEngine
{
public:
    PlcEngine(uint8_t * program);

    void start();
    bool run(uint8_t inputs, uint8_t *outputs);

private:
    uint16_t     m_pc;
    uint8_t    * m_prog;
    uint16_t     m_exitAddress;
    uint16_t     m_newState;
    uint32_t     m_timestamp;

    uint8_t      readArg8();
    uint16_t     readArg16();
    uint16_t     findBlock(uint8_t cmd);
};
