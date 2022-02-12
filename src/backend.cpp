#include "backend.h"

/**
 * @brief Append data to data file
 *
 * @param evName C string that holds name of event
 * @param evDate C string that holds date of event
 */
void appendNodeToFile(char *evName, char *evDate)
{
    // Write event data to data file
    std::fstream data;
    data.open("data.csv", std::ios::app);
    data << evName << "," << evDate << ","
         << "\"Edit me to add description\""
         << ",\n";
}

/**
 * @brief Function that deletes given line of file
 *
 * @param index Line to be deleted from file
 */
void deleteNodeAtIndex(const unsigned index)
{
    // Initialize a counter of lines
    unsigned counter = 0;

    // Open data file in input mode
    std::fstream data;
    data.open("data.csv", std::ios::in);

    std::string line;
    std::string fileContents;

    // Get all data from file except line to be deleted
    while (std::getline(data, line))
    {
        if (counter != index)
        {
            fileContents += line;
            fileContents += "\n";
        }
        counter++;
    }

    // Close the file
    data.close();

    // Open file in output and truncate mode to delete all contents
    // and put in new contents
    data.open("data.csv", std::ios::out | std::ios::trunc);
    data << fileContents;
    data.close();
}

/**
 * @brief Function to initialize data file
 *
 */
void initDataFile()
{
    std::ifstream testFile;
    std::string testString;

    // Try to open data file
    testFile.open("data.csv");

    std::getline(testFile, testString);

    // If data file can't be opened then it doesn't exist
    if (!testFile || testString != "Name,Date,Desc,")
    {
        std::ofstream data;

        // Create a data file
        data.open("data.csv", std::ios::out | std::ios::trunc);

        // Add columns for data
        data << "Name,Date,Desc,";
        data << "\n";

        // Close the file
        data.close();
    }

    testFile.close();
}

EventNode *mergeList(EventNode *left, EventNode *right)
{
    EventNode *res = NULL;

    if (left == NULL)
    {
        return res;
    }
    if (right == NULL)
    {
        return res;
    }

    if (left->date.tm_year <= right->date.tm_year)
    {
        res = left;
        res->next = mergeList(left->next, right);
    }
    else
    {
        res = right;
        res->next = mergeList(left, right->next);
    }

    return res;
}

void splitListInMiddle(EventNode *head, EventNode **startLeft, EventNode **startRight)
{
    EventNode *tail;
    EventNode *beforeMiddle;

    beforeMiddle = head;
    tail = head->next;

    while (tail != NULL)
    {
        tail = tail->next;
        if (tail != NULL)
        {
            tail = tail->next;
            beforeMiddle = beforeMiddle->next;
        }
    }

    *startLeft = head;

    // Instead of passing the node before the middle node
    // pass the middle node
    *startRight = beforeMiddle->next;

    beforeMiddle->next = NULL;
}

void sortList(EventNode **evRef)
{
    EventNode *head = *evRef;

    if (head == NULL || head->next == NULL)
    {
        return;
    }

    EventNode *left;
    EventNode *right;

    splitListInMiddle(head, &left, &right);

    sortList(&left);
    sortList(&right);

    *evRef = mergeList(left, right);
}

/**
 * @brief Function that updates event list from given file
 *
 * @param ev Event node
 * @return int Returns number of events
 */
int updateEventList(EventNode *ev)
{
    std::string dateString;
    std::stringstream dateSStream;

    // Variable to store number of events
    short count = 0;

    // Create an object of type CSVReader and give it the csv data file
    io::CSVReader<3> in("data.csv");

    // Pass it columns where data will be stored
    in.read_header(io::ignore_extra_column, "Name", "Date", "Desc");

    // Reset any previous data in head
    ev->date.tm_year = 0;
    ev->date.tm_mon = 0;
    ev->date.tm_mday = 0;

    // Read from file until data is present
    while (in.read_row(ev->name, dateString, ev->desc))
    {
        // Put dateString into dateSStream, parse the date and clear the stream
        dateSStream << dateString;
        dateSStream >> std::get_time(&(ev->date), "%Y-%m-%d");

        dateSStream.str("");
        dateSStream.clear();

        // Add 1 to tm_mon get accurate month since it returns [0..11]
        ev->date.tm_mon++;
        ev->date.tm_year += 1900;

        // Declare a new node and change it
        ev->next = new EventNode;
        ev = ev->next;

        count++;
    }
    return count;
}