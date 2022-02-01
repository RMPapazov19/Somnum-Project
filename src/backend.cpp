#include "backend.h"

void getNewNode(WINDOW *win)
{
    char name[80];
    int day, month, year;

    mvwprintw(win, 1, 1, "Name:");
    mvwprintw(win, 2, 1, "Day:");
    mvwprintw(win, 3, 1, "Month:");
    mvwprintw(win, 4, 1, "Year:");

    mvwgetstr(win, 1, 6, name);
    mvwscanw(win, 2, 5, "%i", &day);
    mvwscanw(win, 3, 7, "%i", &month);
    mvwscanw(win, 4, 6, "%i", &year);

    std::fstream data;
    data.open("data.csv", std::ios::app);
    data << name << "," << day << "," << month << "," << year << ","
         << "\"Edit me to add description\",\n";
}

void appendNode()
{
    echo();
    WINDOW *win;
    PANEL *pan;
    int maxX, maxY;
    getmaxyx(stdscr, maxY, maxX);
    win = newwin(maxY / 2, maxX / 2, maxY / 4, maxX / 4);
    pan = new_panel(win);
    box(win, 0, 0);
    updatePanels();

    getNewNode(win);

    del_panel(pan);
    delwin(win);
    noecho();
}

void initEventList(EventNode *ev)
{
    std::fstream data;
    std::ifstream *fileTest = new std::ifstream;
    fileTest->open("data.csv");
    if (!(*fileTest))
    {
        data.open("data.csv", std::ios::in | std::ios::app);
        data << "Name,Day,Month,Year,Desc";
        delete fileTest;
        data.close();
    }
    io::CSVReader<5> in("data.csv");
    in.read_header(io::ignore_extra_column, "Name", "Day", "Month", "Year", "Desc");
    while (in.read_row(ev->name, ev->day, ev->month, ev->year, ev->desc))
    {
        ev->next = new EventNode;
        ev = ev->next;
    }
}