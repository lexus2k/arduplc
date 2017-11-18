#include "p_up.h"

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

void upEnter()
{
    g_lcd.clear();
    g_lcd.setCursor(0,0);
    g_lcd.print("BBEPX ...");
    plcResetTime();
    if (readPlcInput( SENSOR_TOP ) == LOW)
    {
        writePlcOutput( SOLENOID_UP, HIGH );
    }
}

void upRun()
{
    if (readPlcInput( SENSOR_TOP ) == HIGH)
    {
        plcChangeState( STATE_REMOVE_BRIQUETTE );
    }
}

void upExit()
{
    writePlcOutput( SOLENOID_UP, LOW );
}

//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

void upCenterEnter()
{
    g_lcd.clear();
    g_lcd.setCursor(0,0);
    g_lcd.print("BBEPX uEHTP ...");
    plcResetTime();
    if (readPlcInput( SENSOR_MIDDLE ) == LOW)
    {
        writePlcOutput( SOLENOID_UP, HIGH );
    }
}

void upCenterRun()
{
    if (readPlcInput( SENSOR_MIDDLE ) == HIGH)
    {
        g_shakes = shakeCount + 1;
        g_finalPress = true;
        delay(middleDelayMs);
        writePlcOutput( SOLENOID_UP, LOW );
        plcChangeState( STATE_SHAKE_LEFT );
    }
}

void upCenterExit()
{
    writePlcOutput( SOLENOID_UP, LOW );
    g_lcd.setCursor(0,0);
    g_lcd.print("CbIPbE ...");
}

