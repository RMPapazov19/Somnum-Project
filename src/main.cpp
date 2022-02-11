#ifdef _WIN32
#include <PDcurses/curses.h>
#include <PDcurses/panel.h>
#else
#include <ncurses.h>
#include <panel.h>
#endif

#include "backend.h"
#include "tui.h"

int main()
{
    WINDOW *windows[3];
    PANEL *panels[3];
    initscr();

    initDataFile();
    initTUI(windows, panels);
    TUI(windows);
    endwin();
}