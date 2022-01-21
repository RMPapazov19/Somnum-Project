#include <iostream>
#include <ncurses.h>
using namespace std;

int main()
{
    initscr();

    mvprintw(5, 10, "Hello ncurses");

    refresh();
    getch();
    endwin();
}