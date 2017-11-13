#include "plc_inputs.h"
#include "plc_outputs.h"
#include "plc_lcd.h"
#include "plc_buttons.h"
#include "plc_sme.h"

#include <Arduino.h>
#include <Wire.h>


static void plc_print_status()
{
    char str[16] = "- - - - - - -";
    g_lcd.setCursor(0, 0);
    g_lcd.print("I 1 2 3 4 5 6 7");
    for(uint8_t i=0; i<plcInputsCount();i++)
    {
       str[i*2] = (readPlcInput(i) == HIGH) ? '*' : '-';
    }
    g_lcd.setCursor(2, 1);
    g_lcd.print(str);
}

static uint8_t s_output = 0;

static void plc_change_output()
{
    if (plcTimeout(2000))
    {
        writePlcOutput(s_output, LOW);
        plcResetTimer();
        s_output++;
        if (s_output >= plcOutputsCount()) s_output = 0;
        writePlcOutput(s_output, HIGH);
    }
}

void plc_manual_diag()
{
    plc_print_status();
    plc_change_output();
    if (g_buttons.isShortPress(0))
    {
        writePlcOutput(s_output, LOW);
        Serial.println("Another way to check BUTTON_1");
    }
}

void plc_manual_diag_enter()
{
    g_lcd.clear();
    plcResetTimer();
    s_output = 0;
    writePlcOutput(s_output, HIGH);
}

