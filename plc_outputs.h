#pragma once

#include <stdint.h>

void writePlcOutput(uint8_t output, int level);
void initPlcOutputs();
void plcDisableOutputs();
int plcOutputsCount();

