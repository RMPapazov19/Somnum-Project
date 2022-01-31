#pragma once

#include <yaml-cpp/yaml.h>
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

void initEventList(EventNode *ev, YAML::Node data);

YAML::Node parseData();

void appendNode(EventNode *ev);