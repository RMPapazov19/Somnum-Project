#include "tui.h"

void updatePanels()
{
    update_panels();
    doupdate();
}

PANEL *createPopupWindow()
{
    WINDOW *win;
    PANEL *pan;
    int maxX, maxY;
    getmaxyx(stdscr, maxY, maxX);
    win = newwin(maxY / 2, maxX / 2, maxY / 4, maxX / 4);
    pan = new_panel(win);
    box(win, 0, 0);
    hide_panel(pan);
    return pan;
}

void handleInput(WINDOW *windows[3], EventNode *ev, PANEL *popup)
{
    switch (getch())
    {
    case 'q':
        exit(0);
        break;
    case 'w':
        wprintw(windows[0], "Up key has been pressed");
        break;
    case 's':
        wprintw(windows[0], "Down key has been pressed");
        break;
    case 'a':
        // TODO: Optimize appending of nodes
        show_panel(popup);
        appendNode();
        updateEventList(ev);
        hide_panel(popup);
        break;
    case 'd':
        wprintw(windows[0], "Delete key has been pressed");
        break;
    case 'h':

        break;
    }
}

void printEventList(WINDOW *displayWin, EventNode *ev)
{
    size_t i = 1;
    while (ev->next != nullptr)
    {
        mvwprintw(displayWin, i, 1, "%s - %i.%i.%i", ev->name.c_str(), ev->day, ev->month, ev->year);
        i++;
        ev = ev->next;
    }
}

void initTUI(WINDOW *windows[3], PANEL *panels[3])
{
    noecho();
    curs_set(0);
    windows[0] = newwin(3, getmaxx(stdscr), 0, 0);
    windows[1] = newwin(getmaxy(stdscr) - 3, 30, 3, 0);
    windows[2] = newwin(getmaxy(stdscr) - 3, getmaxx(stdscr) - 30, 3, 30);

    for (int i = 0; i < 3; ++i)
    {
        box(windows[i], 0, 0);
    }

    panels[0] = new_panel(windows[0]);
    panels[1] = new_panel(windows[1]);
    panels[2] = new_panel(windows[2]);

    mvwprintw(windows[0], 0, 1, " Timeline ");
    mvwprintw(windows[1], 0, 1, " Events ");
    mvwprintw(windows[2], 0, 1, " Event description ");
}

void TUI(WINDOW *windows[3])
{
    EventNode *head = new EventNode;
    PANEL *popup = createPopupWindow();
    updateEventList(head);
    while (true)
    {
        printEventList(windows[1], head);
        updatePanels();
        handleInput(windows, head, popup);
    }
}
