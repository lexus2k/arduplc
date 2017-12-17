#include "p_down.h"

#include "p_states.h"
#include "p_sensors.h"
#include "p_solenoids.h"

#include "plc_inputs.h"
#include "plc_outputs.h"
#include "plc_lcd.h"
#include "plc_settings.h"

#include <Arduino.h>

//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

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
    if (readPlcInput( SENSOR_BOTTOM ) == HIGH)
    {
        plcFault();
    }
}

void downTempExit()
{
    writePlcOutput( SOLENOID_DOWN, LOW );
}


//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////


void downCenterEnter()
{
    g_lcd.clear();
    g_lcd.setCursor(0,0);
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
        if (prePressingMode)
        {
            g_finalPress = false;
        }
        else
        {
            g_finalPress = true;
        }
    }
    if (readPlcInput( SENSOR_BOTTOM ) == HIGH)
    {
        plcFault();
    }
}

void downCenterExit()
{
    writePlcOutput( SOLENOID_DOWN, LOW );
    g_lcd.setCursor(0,0);
    g_lcd.print("CbIPbE ...");
}

//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

void downEnter()
{
    g_lcd.clear();
    g_lcd.setCursor(0,1);
    g_lcd.print("Press ...");
    plcResetTime();
    if (readPlcInput( SENSOR_BOTTOM ) == LOW)
    {
        writePlcOutput( SOLENOID_DOWN, HIGH );
    }
}

void downRun()
{
    if (readPlcInput( SENSOR_BOTTOM ) == HIGH)
    {
        plcChangeState( STATE_UP );
    }
}

void downExit()
{
    writePlcOutput( SOLENOID_DOWN, LOW );
    delay(pressDelayMs);
}

