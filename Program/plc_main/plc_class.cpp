#include "plc_class.h"

#include <Arduino.h>

PlcController::PlcController()
{
    m_inputsCount = 0;
    m_outputsCount = 0;
}

void PlcController::setup()
{
    for (uint8_t i=0; i<m_outputsCount; i++)
    {
        pinMode(m_outputs[i], OUTPUT);
        digitalWrite(m_outputs[i], LOW);
    }
    for (uint8_t i=0; i<m_inputsCount; i++)
    {
        pinMode(m_inputs[i], INPUT_PULLUP);
    }
}

void PlcController::reset()
{
}

void PlcController::output(uint8_t n, bool level)
{
    if (n <= m_outputsCount)
    {
        digitalWrite(m_outputs[n], level ? HIGH: LOW);
    }
}

bool PlcController::input(uint8_t n)
{
    if (n <= m_inputsCount)
    {
        /* Invert values, because input sensors use LOW as active. see Schematics */
        if (LOW == digitalRead(m_inputs[n])) return true;
    }
    return false;
}


