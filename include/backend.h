#pragma once

#include <csv.h>
#include <string>
#include <fstream>
#include <iostream>
#include "tui.h"

struct EventNode
{
    int day, month, year;
    std::string name;
    std::string desc;
    struct EventNode *next = NULL;
};

void updateEventList(EventNode *ev);

void appendNode();