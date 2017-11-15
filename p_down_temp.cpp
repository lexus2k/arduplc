#include "p_down_temp.h"

#include "p_states.h"
#include "p_sensors.h"
#include "p_solenoids.h"

#include "plc_inputs.h"
#include "plc_outputs.h"
#include "plc_lcd.h"
#include "plc_settings.h"

#include <Arduino.h>

void downTempEnter()
{
    g_lcd.clear();
    g_lcd.setCursor(0,1);
    g_lcd.print("Pre-press ...");
    plcResetTime();
    if (readPlcInput( SENSOR_BOTTOM_TEMP ) == LOW)
    {
        writePlcOutput( SOLENOID_DOWN, HIGH );
    }
}

void downTempRun()
{
    if (readPlcInput( SENSOR_BOTTOM_TEMP ) == HIGH)
    {
        plcChangeState( STATE_UP_MIDDLE );
    }
}

void downTempExit()
{
    writePlcOutput( SOLENOID_DOWN, LOW );
}

