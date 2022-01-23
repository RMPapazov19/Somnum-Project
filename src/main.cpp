#ifdef _WIN32
#include <curses.h>
#include <panel.h>
#else
#include <ncurses.h>
#include <panel.h>
#endif

#include "tui.h"
int main()
{
    WINDOW *windows[3];
    PANEL *panels[3];
	initscr();
	cbreak();
	noecho();
    initTUI(windows, panels);
    TUI(windows);
	endwin();
}