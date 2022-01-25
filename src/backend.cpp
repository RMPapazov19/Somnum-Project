#include "backend.h"

void initEventList(EventNode *ev,YAML::Node data)
{
    size_t i = 0;
    while(i < data.size()){
        ev->name = data[i]["name"].as<std::string>();
        ev->day = data[i]["day"].as<int>();
        ev->month = data[i]["month"].as<int>();
        ev->year = data[i]["year"].as<int>();
        ev->desc = data[i]["desc"].as<std::string>();
        i++;
        ev->next = new EventNode();
        ev = ev->next;
    } 
}