#include "p_down_center.h"

#include "p_states.h"
#include "p_sensors.h"
#include "p_solenoids.h"

#include "plc_inputs.h"
#include "plc_outputs.h"
#include "plc_lcd.h"
#include "plc_settings.h"

#include <Arduino.h>

void downCenterEnter()
{
    g_lcd.clear();
    g_lcd.setCursor(0,1);
    g_lcd.print("BHU3 uEHTP ...");
    plcResetTime();
    if (readPlcInput( SENSOR_MIDDLE ) == LOW)
    {
        writePlcOutput( SOLENOID_DOWN, HIGH );
    }
}

void downCenterRun()
{
    if (readPlcInput( SENSOR_MIDDLE ) == HIGH)
    {
        plcChangeState( STATE_SHAKE_RIGHT );
        g_shakes = shakeCount;
    }
}

void downCenterExit()
{
    writePlcOutput( SOLENOID_DOWN, LOW );
}

