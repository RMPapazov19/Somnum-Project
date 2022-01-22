#include "tui.h"

void updatePanels()
{
    update_panels();
    doupdate();
}

bool handleInput()
{
    switch (getch())
    {
    case 'q':
    return true;
        break;
    }
    return false;
}

void initTUI(WINDOW *windows[3], PANEL *panels[3])
{
    windows[0] = newwin(3, getmaxx(stdscr), 0, 0);
    windows[1] = newwin(getmaxy(stdscr) - 3, 30, 3, 0);
    windows[2] = newwin(getmaxy(stdscr) - 3, getmaxx(stdscr) - 30, 3, 30);
    for(int i = 0; i < 3; ++i)
    {
        box(windows[i], 0, 0);
    }
    panels[0] = new_panel(windows[0]);
    panels[1] = new_panel(windows[1]);
    panels[2] = new_panel(windows[2]);
}



void TUI(WINDOW *windows[3])
{
    while (true)
    {
        updatePanels();
        if(handleInput())
        {
            return;
        }
    }
}