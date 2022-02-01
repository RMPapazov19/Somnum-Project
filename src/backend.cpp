#include "backend.h"

EventNode *getTail(EventNode *ev)
{
    while (ev->next != NULL)
    {
        ev = ev->next;
    }
    return ev;
}

void appendNode(EventNode *ev)
{
    echo();
    int maxX, maxY;
    getmaxyx(stdscr, maxY, maxX);
    WINDOW *inputWin = newwin(maxY / 2, maxX / 2, maxY / 4, maxX / 4);
    PANEL *inputPanel = new_panel(inputWin);
    box(inputWin, 0, 0);
    char name[80];
    int day, month, year;

    updatePanels();

    mvwprintw(inputWin, 1, 1, "Name:");
    mvwprintw(inputWin, 2, 1, "Day:");
    mvwprintw(inputWin, 3, 1, "Month:");
    mvwprintw(inputWin, 4, 1, "Year:");

    mvwgetstr(inputWin, 1, 6, name);
    mvwscanw(inputWin, 2, 5, "%i", &day);
    mvwscanw(inputWin, 3, 7, "%i", &month);
    mvwscanw(inputWin, 4, 6, "%i", &year);

    del_panel(inputPanel);
    delwin(inputWin);
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