#include "backend.h"

void appendNode()
{
    echo();

    WINDOW *win = panel_window(panel_below(NULL));
    char name[80];
    unsigned day, month;
    int year;

    mvwprintw(win, 1, 1, "Name:");
    mvwprintw(win, 2, 1, "Day (Number):");
    mvwprintw(win, 3, 1, "Month (Number):");
    mvwprintw(win, 4, 1, "Year (Number):");

    mvwgetstr(win, 1, 6, name);
    box(win, 0, 0);
    mvwscanw(win, 2, 16, "%u", &day);
    box(win, 0, 0);
    mvwscanw(win, 3, 18, "%u", &month);
    box(win, 0, 0);
    mvwscanw(win, 4, 17, "%i", &year);

    wclear(win);
    box(win, 0, 0);

    std::fstream data;
    data.open("data.csv", std::ios::app);
    data << name << "," << day << "," << month << "," << year << ","
         << "\"Edit me to add description\",\n";

    noecho();
}

void deleteNodeAtIndex(const unsigned index)
{
    unsigned counter = 0;
    std::fstream data;
    data.open("data.csv", std::ios::in);
    std::string line;
    std::string contents;
    while (std::getline(data, line))
    {
        if (counter != index)
        {
            contents += line;
            contents += "\n";
        }
        counter++;
    }
    data.close();
    data.open("data.csv", std::ios::out | std::ios::trunc);
    data << contents;
    data.close();
}

void updateEventList(EventNode *ev)
{
    std::fstream data;
    std::ifstream *fileTest = new std::ifstream;
    fileTest->open("data.csv");
    if (!(*fileTest))
    {
        data.open("data.csv", std::ios::in | std::ios::app);
        data << "Name,Day,Month,Year,Desc,";
        data << "\n";
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