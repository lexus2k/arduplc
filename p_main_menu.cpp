#include "p_main_menu.h"

#include "p_states.h"
#include "plc_settings.h"

#include "plc_inputs.h"
#include "plc_outputs.h"
#include "plc_lcd.h"
#include "plc_buttons.h"
#include "plc_sme.h"

#include "tiny_menu.h"

enum
{
    MENU_START,
    MENU_AUTOMODE,
    MENU_PRE_PRESS,
    MENU_LOAD_CYCLES,
    MENU_PRESS_TIME,
    MENU_SHAKE_TIME,
    MENU_UP_TIME,
    MENU_SAVE_SETTINGS,
    MENU_DIAG,
};

static MenuItem menuItems[] =
{
    { MENU_START,       "CTAPT" },
    { MENU_AUTOMODE,    "ABTOMAT", MENU_ITEM_BOOL, &automaticMode },
    { MENU_PRE_PRESS,   "\x01O\x02\x01PECCOB.", MENU_ITEM_BOOL, &prePressingMode },
    { MENU_LOAD_CYCLES, "\x01POXO\x02""bl", MENU_ITEM_UINT8, &shakeCount },
    { MENU_PRESS_TIME,  "\x02""ABUTb", MENU_ITEM_TIME16, &pressDelayMs },
    { MENU_SHAKE_TIME,  "3A\xA2Py3.", MENU_ITEM_TIME16, &shakeDelayMs },
    { MENU_UP_TIME,     "\01O\02bEM", MENU_ITEM_TIME16, &middleDelayMs },
    { MENU_SAVE_SETTINGS, "COXPAHUTb" },
    { MENU_DIAG,        "\x02UA\xA2HOCTUKA"},
};

static TinyMenu mainMenu(menuItems, sizeof(menuItems) / sizeof(menuItems[0]));

static void registerArrow()
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
}

static void registerP()
{
    uint8_t p_letter[8] = {
        B00011111,
        B00010001,
        B00010001,
        B00010001,
        B00010001,
        B00010001,
        B00010001,
        B00000000,
    };
    g_lcd.createChar(1, p_letter);
}

static void registerD()
{
    uint8_t d_letter[8] = {
        B00000111,
        B00000101,
        B00000101,
        B00001001,
        B00001001,
        B00001001,
        B00011111,
        B00010001,
    };
    g_lcd.createChar(2, d_letter);
}

void mainMenuEnter()
{
    registerArrow();
    registerP();
    registerD();
    g_lcd.backlight();
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
            case MENU_SAVE_SETTINGS:
                saveSettings();
                tone(8, 1000); delay(300);
                tone(8, 500); delay(200);
                tone(8, 200); delay(100);
                noTone(8);
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
                mainMenu.show();
                break;
            case MENU_PRE_PRESS:
                prePressingMode = prePressingMode == 0 ? 1: 0;
                mainMenu.show();
                break;
            case MENU_LOAD_CYCLES:
                shakeCount++; if (shakeCount>5) shakeCount=2;
                mainMenu.show();
                break;
            case MENU_PRESS_TIME:
                pressDelayMs+=1000; if (pressDelayMs>10000) pressDelayMs = 1000;
                mainMenu.show();
                break;
            case MENU_SHAKE_TIME:
                shakeDelayMs+=100; if (shakeDelayMs>900) shakeDelayMs = 100;
                mainMenu.show();
                break;
            case MENU_UP_TIME:
                middleDelayMs+=50; if (middleDelayMs>400) middleDelayMs = 100;
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
