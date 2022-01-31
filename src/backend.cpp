#include "backend.h"

void initEventList(EventNode *ev, YAML::Node data)
{
    size_t i = 0;
    while (i < data.size())
    {
        ev->name = data[i]["name"].as<std::string>();
        ev->day = data[i]["day"].as<int>();
        ev->month = data[i]["month"].as<int>();
        ev->year = data[i]["year"].as<int>();
        ev->desc = data[i]["desc"].as<std::string>();
        i++;
        ev->next = new EventNode;
        ev = ev->next;
    }
}

YAML::Node parseData()
{
    try
    {
        return YAML::LoadFile("data.yaml");
    }
    catch (...)
    {
        std::ofstream dat("data.yaml");
        return YAML::LoadFile("data.yaml");
    }
}

void appendNode(EventNode *ev)
{
    echo();
    while (ev->next != NULL)
    {
        ev = ev->next;
    }
    ev->next = new EventNode;
    ev = ev->next;
    int maxX, maxY;
    getmaxyx(stdscr, maxY, maxX);
    WINDOW *inputWin = newwin(maxY / 2, maxX / 2, maxY / 4, maxX / 4);
    PANEL *inputPanel = new_panel(inputWin);
    box(inputWin, 0, 0);

    char name[80];

    updatePanels();

    mvwprintw(inputWin, 1, 1, "Name:");
    mvwgetstr(inputWin, 1, 6, name);

    del_panel(inputPanel);
    delwin(inputWin);
    noecho();
}