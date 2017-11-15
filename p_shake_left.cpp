#include "p_shake_left.h"

#include "p_states.h"
#include "p_sensors.h"
#include "p_solenoids.h"

#include "plc_inputs.h"
#include "plc_outputs.h"
#include "plc_lcd.h"
#include "plc_settings.h"

#include <Arduino.h>

void shakeLeftEnter()
{
    if (readPlcInput( SENSOR_PULLED ) == LOW)
    {
        writePlcOutput( SOLENOID_PULL_OUT, HIGH );
    }
}

void shakeLeftRun()
{
    if (readPlcInput( SENSOR_PULLED ) == HIGH)
    {
        g_shakes--;
        if (g_shakes)
        {
            plcChangeState( STATE_SHAKE_RIGHT );
        }
        else
        {
            plcChangeState( STATE_REMOVE );
        }
    }
}

void shakeLeftExit()
{
    writePlcOutput( SOLENOID_PULL_OUT, LOW );
}

