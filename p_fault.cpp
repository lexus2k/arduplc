#include "p_fault.h"

#include "p_states.h"
#include "p_sensors.h"
#include "p_solenoids.h"

#include "plc_inputs.h"
#include "plc_outputs.h"
#include "plc_lcd.h"

#include <Arduino.h>

void faultEnter()
{
    g_lcd.clear();
    g_lcd.setCursor(0,1);
    g_lcd.print("FAULT ...");
    initPlcOutputs();
}

void faultRun()
{
}

void faultExit()
{
}

