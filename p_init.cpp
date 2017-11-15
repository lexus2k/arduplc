#include "p_init.h"

#include "p_states.h"
#include "p_sensors.h"
#include "p_solenoids.h"

#include "plc_inputs.h"
#include "plc_outputs.h"
#include "plc_lcd.h"

#include <Arduino.h>

void initEnter()
{
    g_lcd.clear();
    g_lcd.setCursor(0,1);
    g_lcd.print("HACTPOUKA ...");
    plcSetFaultState(STATE_FAULT);
    tone(8, 200, 1000);
    plcResetTime();
    if (readPlcInput(SENSOR_REMOVED) == LOW)
    {
        writePlcOutput( SOLENOID_REMOVE, HIGH );
    }
    if (readPlcInput(SENSOR_TOP) == LOW)
    {
        writePlcOutput( SOLENOID_UP, HIGH );
    }
}

void initRun()
{
    uint8_t passed = 0;
    if (readPlcInput(SENSOR_TOP) == HIGH)
    {
        writePlcOutput( SOLENOID_UP, LOW );
        passed++;
    }
    if (readPlcInput(SENSOR_REMOVED) == HIGH)
    {
        writePlcOutput( SOLENOID_REMOVE, LOW );
        passed++;
    }
/*    else if (plcStateTime() >= 2000)
    {
        plcChangeState( STATE_FAULT );
    }*/
    if ( passed == 2 )
    {
        plcChangeState( STATE_REMOVE_BRIQUETTE );
    }
}

void initExit()
{
    writePlcOutput( SOLENOID_REMOVE, LOW );
    writePlcOutput( SOLENOID_UP, LOW );
}

