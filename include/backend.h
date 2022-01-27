#pragma once

#ifdef _WIN32
#include <yaml-cpp/yaml.h>
#else
#include <yaml-cpp/yaml.h>
#endif

#include <string>
#include <fstream>
#include <iostream>

struct EventNode
{
    int day, month, year;
    std::string name;
    std::string desc;
    struct EventNode *next = nullptr;
};

void initEventList(EventNode *ev, YAML::Node data);

YAML::Node parseData();