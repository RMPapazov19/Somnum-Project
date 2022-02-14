#pragma once

#include <csv.h>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <ctime>

/**
 * @brief Node of event linked list
 *
 */
struct EventNode
{
    std::tm date;
    std::string name;
    std::string desc;
    struct EventNode *next = NULL;
};

/**
 * @brief Function that updates event list from given file
 *
 * @param ev Event node
 * @return int Returns number of events
 */
int updateEventList(EventNode *ev);

/**
 * @brief Append data to data file
 *
 * @param evName C string that holds event name
 * @param evDate C string that holds event date
 */
void appendNodeToFile(char *name, char *date);

/**
 * @brief Function that deletes given line from file
 *
 * @param index Line to be deleted from file
 */
void deleteNodeAtIndex(const unsigned index);

/**
 * @brief Function that sorts linked list using merge sort
 * 
 * @param evRef Pointer to event list
 */
void sortList(EventNode **evRef);

/**
 * @brief Function to initialize data file
 *
 */
void initDataFile();