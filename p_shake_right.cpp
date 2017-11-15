#include "p_shake_right.h"

#include "p_states.h"
#include "p_sensors.h"
#include "p_solenoids.h"

#include "plc_inputs.h"
#include "plc_outputs.h"
#include "plc_lcd.h"
#include "plc_settings.h"

#include <Arduino.h>

void shakeRightEnter()
{
    if (readPlcInput( SENSOR_REMOVED ) == LOW)
    {
        writePlcOutput( SOLENOID_REMOVE, HIGH );
    }
}

void shakeRightRun()
{
    if (plcStateTime() >= shakeDelayMs)
    {
        plcChangeState( STATE_SHAKE_LEFT );
    }
    if (readPlcInput( SENSOR_REMOVED ) == HIGH)
    {
        plcChangeState( STATE_FAULT );
    }
}

void shakeRightExit()
{
    writePlcOutput( SOLENOID_REMOVE, LOW );
}

