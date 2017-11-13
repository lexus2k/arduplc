#include "plc_poweron.h"

#include "plc_inputs.h"
#include "plc_outputs.h"
#include "plc_lcd.h"
#include "plc_buttons.h"
#include "plc_sme.h"

#include "tiny_menu.h"

static const char *menuItems[] =
{
    "CTAPT",
    "3ADEP#KA",
    "CTATUCTUKA",
    "HACTPOUKA",
    "XOPOWO",
    "DUA\x00A2HOCTUKA",
    "TECTUPOBAHUE",
    "menu item 8",
};

static TinyMenu mainMenu(menuItems, sizeof(menuItems) / sizeof(char *));

void powerOnEnter()
{
    uint8_t arrow[8] = {
        B00001000,
        B00001100,
        B00001110,
        B00001111,
        B00001110,
        B00001100,
        B00001000,
        B00000000,
    };
    initPlcInputs();
    initPlcOutputs();
    g_lcd.createChar(0, arrow);
    g_lcd.backlight();
    g_lcd.clear();
    g_lcd.setCursor(0, 0);
    g_lcd.print("Powering on...");
    mainMenu.show();
}

void powerOnRun()
{
    if (g_buttons.isShortPress(PLC_BUTTON_UP))
    {
        mainMenu.up();
        mainMenu.show();
    }
    if (g_buttons.isShortPress(PLC_BUTTON_DOWN))
    {
        mainMenu.down();
        mainMenu.show();
    }
}



