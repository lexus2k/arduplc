#include "p_main_menu.h"

#include "p_states.h"
#include "plc_settings.h"

#include "plc_inputs.h"
#include "plc_outputs.h"
#include "plc_lcd.h"
#include "plc_buttons.h"
#include "plc_sme.h"

#include "tiny_menu.h"

static char *autoStr = "ABTOMAT=   ";

enum
{
    MENU_START,
    MENU_AUTOMODE,
    MENU_DIAG,
};

static MenuItem menuItems[] =
{
    { MENU_START, "CTAPT" },
    { MENU_AUTOMODE, autoStr },
    { MENU_DIAG, "DUA\x00A2HOCTUKA"},
};

static TinyMenu mainMenu(menuItems, sizeof(menuItems) / sizeof(menuItems[0]));

static void updateMenuItemsContent()
{
    if (automaticMode == 0)
    {
        strcpy(&autoStr[8], "OFF");
    }
    else
    {
        strcpy(&autoStr[8], "ON");
    }
}

void mainMenuEnter()
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
    g_lcd.createChar(0, arrow);
    g_lcd.backlight();
    updateMenuItemsContent();
    mainMenu.show();
}

void mainMenuRun()
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
    if (g_buttons.isLongHold(PLC_BUTTON_SELECT, millis(), 3000))
    {
        switch (mainMenu.selection())
        {
            case MENU_START:
                plcChangeState(STATE_INIT);
                break;
            default:
                break;
        }
    }
    if (g_buttons.isShortPress(PLC_BUTTON_SELECT))
    {
        switch (mainMenu.selection())
        {
            case MENU_DIAG:
                plcChangeState(STATE_PLC_DIAG);
                break;
            case MENU_AUTOMODE:
                automaticMode = automaticMode == 0 ? 1: 0;
                updateMenuItemsContent();
                mainMenu.show();
                break;
            default:
                break;
        }
    }
}

void mainMenuExit()
{
}
