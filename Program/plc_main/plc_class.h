#pragma once

#include <stdint.h>


class PlcController
{
public:
    PlcController();
    void setup();

    void reset();
    void output(uint8_t n, bool level);
    bool input(uint8_t n);

private:
    static const uint8_t MAX_INPUTS  = 16;
    static const uint8_t MAX_OUTPUTS = 16;
    uint8_t m_inputs[MAX_INPUTS];
    uint8_t m_outputs[MAX_INPUTS];
    uint8_t m_inputsCount;
    uint8_t m_outputsCount;
};


