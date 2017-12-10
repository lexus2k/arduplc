#include "plc_outputs.h"

#include <Arduino.h>

const static uint8_t s_outputPins[] =
{
    7,
    6,
    5,
    4,
    3,
    2,
};

void writePlcOutput(uint8_t output, int level)
{
    digitalWrite(s_outputPins[output], level);
}

int plcOutputsCount()
{
    return sizeof(s_outputPins)/sizeof(s_outputPins[0]);
}

void initPlcOutputs()
{
    for (uint8_t i=0; i<sizeof(s_outputPins); i++)
    {
        pinMode(s_outputPins[i], OUTPUT);
        digitalWrite(s_outputPins[i], LOW);
    }
}

void plcDisableOutputs()
{
    for (uint8_t i=0; i<sizeof(s_outputPins); i++)
    {
        digitalWrite(s_outputPins[i], LOW);
    }
}
