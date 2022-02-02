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
    win = newwin(8, 28, maxY / 4 + 4, maxX / 4 + 14);
    pan = new_panel(win);
    box(win, 0, 0);
    hide_panel(pan);
    return pan;
}

void displayHelp()
{
    WINDOW *win = panel_window(panel_below(NULL));
    mvwprintw(win, 1, 1, "| Keybind | Action       |");
    mvwprintw(win, 2, 1, "--------------------------");
    mvwprintw(win, 3, 1, "|    a    | Add event    |");
    mvwprintw(win, 4, 1, "|    z    | Delete event |");
    mvwprintw(win, 5, 1, "|    w    | Go up        |");
    mvwprintw(win, 6, 1, "|    s    | Go down      |");
    updatePanels();
    getch();

    wclear(win);
    box(win, 0, 0);
}

void handleInput(short &highlight, EventNode *ev, PANEL *popup)
{
    switch (getch())
    {
    case 'q':
        exit(0);
        break;
    case 'w':
        highlight--;
        break;
    case 's':
        highlight++;
        break;
    case 'a':
        show_panel(popup);
        appendNode();
        updateEventList(ev);
        hide_panel(popup);
        break;
    case 'z':
        break;
    case 'h':
        show_panel(popup);
        displayHelp();
        hide_panel(popup);
        break;
    }
    if (highlight < 1)
    {
        highlight = 1;
    }
}

void printEventList(WINDOW *win[3], EventNode *ev, const short highlight)
{
    short i = 1;
    while (ev->next != nullptr)
    {
        if (highlight == i)
        {
            wattron(win[1], A_STANDOUT);
            mvwprintw(win[1], i, 1, "%s - %i.%i.%i", ev->name.c_str(), ev->day, ev->month, ev->year);
            wattroff(win[1], A_STANDOUT);
            wclear(win[2]);
            box(win[2], 0, 0);
            mvwprintw(win[2], 1, 1, "%s", ev->desc.c_str());
        }
        else
        {
            mvwprintw(win[1], i, 1, "%s - %i.%i.%i", ev->name.c_str(), ev->day, ev->month, ev->year);
        }
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
    short highlight = 1;
    while (true)
    {
        printEventList(windows, head, highlight);
        updatePanels();
        handleInput(highlight, head, popup);
    }
}
