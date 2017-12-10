#pragma once

#include <stdint.h>

enum
{
    MENU_ITEM_NORMAL = 0,
    MENU_ITEM_SUBMENU,
    MENU_ITEM_BOOL,
    MENU_ITEM_UINT8,
    MENU_ITEM_TIME16,
};


typedef struct MenuItem
{
    uint8_t id;
    const char *text;
    uint8_t type;
    void *data;
};

class TinyMenu
{
public:
    TinyMenu(MenuItem *items, uint8_t count);

    void show();
    void up();
    void down();
    uint8_t selection();

private:
    /// list of menu items of the menu
    MenuItem *m_items;
    /// count of menu items in the menu
    uint8_t     m_count;
    /// currently selected item. Internally updated.
    uint8_t     m_selection;
    /// selected item, when last redraw operation was performed. Internally updated.
    uint8_t     m_oldSelection;
    /// position of menu scrolling. Internally updated
    uint8_t     m_scrollPosition;

    void        calcPos();
    uint8_t     maxItems();
    void        drawMenuItem(uint8_t index);
};