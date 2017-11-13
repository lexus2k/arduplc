#include "tiny_menu.h"
#include "plc_lcd.h"

#ifndef min
#define min(x,y) ((x)<(y)?(x):(y))
#endif

#ifndef max
#define max(x,y) ((x)>(y)?(x):(y))
#endif


TinyMenu::TinyMenu(const char **items, uint8_t count)
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
    g_lcd.print(m_items[index]);
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
