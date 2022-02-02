#pragma once

#include <csv.h>
#include <string>
#include <fstream>
#include <iostream>
#include "tui.h"

/**
 * @brief Node which contains all data about event and pointer to next node
 * 
 */
struct EventNode
{
    int day, month, year;
    std::string name;
    std::string desc;
    struct EventNode *next = NULL;
};

/**
 * @brief Function to update linked list of events
 * 
 * @param ev head node of linked list
 */
void updateEventList(EventNode *ev);

/**
 * @brief Add event data to end of data file
 * 
 */
void appendNode();

/**
 * @brief Delete event data from file at given line
 * 
 * @param index Line of event file to be deleted
 */
void deleteNodeAtIndex(const unsigned index);