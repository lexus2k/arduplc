/*
    Copyright (C) 2017 - 2018 Alexey Dynda

    This file is part of Ardu PLC project.

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include <stdint.h>

enum
{
    MENU_ITEM_NORMAL = 0,
    MENU_ITEM_INFO,
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
    void setSelection(uint8_t id);

private:
    /// list of menu items of the menu
    MenuItem *  m_items;
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