#include "plc_engine.h"
#include "plc_inputs.h"
#include "plc_outputs.h"
#include "plc_sme.h"
#include "p_states.h"
#include "plc_lcd.h"
#include "plc_buttons.h"

#include <Arduino.h>
#include <Wire.h>

void setup()
{
    plcInitSme( programStates, programStatesCount(), STATE_POWER_ON );
}

void loop()
{
    g_buttons.update();
    plcRunSme();
    if (plcGetState() > STATE_PASSIVE)
    {
        if (g_buttons.isShortPress())
        {
            plcChangeState( STATE_MAIN_MENU );
            plcDisableOutputs();
            tone(8, 200); delay(300);
            tone(8, 500); delay(200);
            tone(8, 1000); delay(100);
            noTone(8);
        }
    }
}
