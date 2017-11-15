#include "p_remove_briq.h"

#include "p_states.h"
#include "p_sensors.h"
#include "p_solenoids.h"

#include "plc_inputs.h"
#include "plc_outputs.h"
#include "plc_lcd.h"
#include "plc_settings.h"

#include <Arduino.h>

void removeBriquetteEnter()
{
    g_lcd.clear();
    g_lcd.setCursor(0,1);
    g_lcd.print("y6upaeM ...");
    plcResetTime();
    if (readPlcInput( SENSOR_PULLED ) == LOW)
    {
        writePlcOutput( SOLENOID_PULL_OUT, HIGH );
    }
}

void removeBriquetteRun()
{
    if (readPlcInput(SENSOR_PULLED) == HIGH)
    {
        plcChangeState( STATE_DOWN_CENTER );
    }
}

void removeBriquetteExit()
{
    writePlcOutput( SOLENOID_PULL_OUT, LOW );
}

