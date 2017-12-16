#include "plc_inputs.h"

#include <Arduino.h>

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

int plcInputsCount()
{
    return sizeof(s_inputPins)/sizeof(s_inputPins[0]);
}

int readPlcInput(uint8_t input)
{
    /* Invert values, because input sensors use LOW as active. see Schematics */
    if (LOW == digitalRead(s_inputPins[input])) return HIGH;
    return LOW;
}

void initPlcInputs()
{
    for (uint8_t i=0; i<sizeof(s_inputPins); i++)
    {
        pinMode(s_inputPins[i], INPUT_PULLUP);
    }
}
