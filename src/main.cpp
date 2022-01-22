#ifdef _WIN32
#include <curses.h>
#else
#include <ncurses.h>
#endif

int main()
{
    initscr();

    mvprintw(5, 10, "Hello ncurses");

    refresh();
    getch();
    endwin();
}