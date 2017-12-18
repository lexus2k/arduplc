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

#include "tiny_menu.h"
#include "plc_lcd.h"

#ifndef min
#define min(x,y) ((x)<(y)?(x):(y))
#endif

#ifndef max
#define max(x,y) ((x)>(y)?(x):(y))
#endif


TinyMenu::TinyMenu(MenuItem *items, uint8_t count)
    :m_items(items)
    ,m_count(count)
    ,m_selection(0)
    ,m_oldSelection(0)
    ,m_scrollPosition(0)
{
}


void TinyMenu::calcPos()
{
    if ( m_selection < m_scrollPosition )
    {
        m_scrollPosition = m_selection;
    }
    else if ( m_selection - m_scrollPosition > maxItems() - 1)
    {
        m_scrollPosition =  m_selection - maxItems() + 1;
    }
}

uint8_t TinyMenu::maxItems()
{
    return 2;
}

void TinyMenu::down()
{
    if (m_selection < m_count - 1)
    {
        m_selection++;
    }
    else
    {
        m_selection = 0;
    }
}

void TinyMenu::up()
{
    if (m_selection > 0)
    {
        m_selection--;
    }
    else
    {
        m_selection = m_count - 1;
    }
}

void TinyMenu::drawMenuItem(uint8_t index)
{
    if (index == m_selection)
    {
        g_lcd.setCursor(0, index - m_scrollPosition);
        g_lcd.write(0);
    }
    else
    {
        g_lcd.setCursor(1, index - m_scrollPosition);
    }
    g_lcd.print(m_items[index].text);
    if (m_items[index].type != MENU_ITEM_NORMAL)
    {
        switch (m_items[index].type)
        {
            case MENU_ITEM_BOOL:
                g_lcd.setCursor(16-4, index - m_scrollPosition);
                g_lcd.print("=");
                g_lcd.print(( *(static_cast<uint8_t *>(m_items[index].data)) == 0) ?
                      "HET": "\x02""A");
                break;
            case MENU_ITEM_UINT8:
                g_lcd.setCursor(16-4, index - m_scrollPosition);
                g_lcd.print("=");
                g_lcd.print( *(static_cast<uint8_t *>(m_items[index].data)) );
                break;
            case MENU_ITEM_TIME16:
            {
                uint16_t t = *(static_cast<uint16_t *>(m_items[index].data));
                g_lcd.setCursor(16-6, index - m_scrollPosition);
                g_lcd.print(":");
                if (t<1000)
                {
                    g_lcd.print( t );
                    g_lcd.print( "mc" );
                }
                else
                {
                    g_lcd.print( (t+499)/1000 );
                    g_lcd.print( "cek" );
                }
                break;
            }
            default:
                break;
        }
    }
}

void TinyMenu::show()
{
    g_lcd.clear();
    calcPos();
    for (uint8_t i = m_scrollPosition; i < min(m_count, m_scrollPosition + maxItems()); i++)
    {
        drawMenuItem(i);
    }
    m_oldSelection = m_selection;
}

uint8_t TinyMenu::selection()
{
    return m_items[m_selection].id;
}
