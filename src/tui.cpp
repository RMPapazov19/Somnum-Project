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

void printEventList(WINDOW *displayWin,EventNode *ev)
{
    size_t i = 1;
    while(ev->next != nullptr)
    {
        mvwprintw(displayWin, i, 1, "%s - %i.%i.%i", ev->name.c_str(), ev->day, ev->month, ev->year);
        i++;
        ev = ev->next;
    }
}

void initTUI(WINDOW *windows[3], PANEL *panels[3])
{
    cbreak();
	noecho();
    curs_set(0);

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
    YAML::Node data = parseData();
    EventNode *head = new EventNode;
    while (true)
    {
        updatePanels();
        initEventList(head, data);
        printEventList(windows[1], head);
        if(handleInput())
        {
            return;
        }
        
    }
}