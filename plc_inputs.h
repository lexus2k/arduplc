#pragma once

#include <stdint.h>

int plcInputsCount();
int readPlcInput(uint8_t input);
void initPlcInputs();
