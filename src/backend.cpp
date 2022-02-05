#include "backend.h"

/**
 * @brief Add event data to end of data file
 *
 */
void appendNode()
{
    // Turn on printing user input to screen
    echo();

    // Get the popup window
    WINDOW *win = panel_window(panel_below(NULL));

    // Declare variables corresponding to collumns in .csv file
    char name[80];
    char date[10];
    std::stringstream ssdate;

    // Print operation in the corner of window
    mvwprintw(win, 0, 1, " Add event ");

    // Print all options
    mvwprintw(win, 1, 1, "Name:");
    mvwprintw(win, 2, 1, "Date:");
    mvwprintw(win, 3, 1, "YYYY-MM-DD = ");

    // Get input for all options
    wmove(win, 1, 6);
    mvwgetstr(win, 1, 6, name);
    box(win, 0, 0);
    mvwprintw(win, 0, 1, " Add event ");
    wmove(win, 3, 14);
    mvwgetstr(win, 3, 14, date);

    // Clear popup window
    wclear(win);
    box(win, 0, 0);

    // Write event data to data file
    std::fstream data;
    std::string dateString(date);
    data.open("data.csv", std::ios::app);
    data << name << "," << dateString << ","
         << "\"Edit me to add description\""
         << ",\n";

    // Turn off printing user input to screen
    noecho();
}

/**
 * @brief Delete event data from file at given line
 *
 * @param index Line of event file to be deleted
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
 * @brief Function to update linked list of events
 *
 * @param ev head node of linked list
 */
int updateEventList(EventNode *ev)
{
    std::fstream data;
    std::ifstream testFile;

    std::string dateString;
    std::stringstream dateSStream;

    // Variable to store number of events
    short count = 0;

    // Try to open data file
    testFile.open("data.csv");

    // If data file can't be opened then it doesn't exist
    if (!testFile)
    {
        // Create a data file
        data.open("data.csv", std::ios::out | std::ios::trunc);

        // Add columns for data
        data << "Name,Date,Desc,";
        data << "\n";

        // Close the file
        data.close();
    }
    testFile.close();

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

        // Add 1 to get accurate date
        // If input was not correct it sets tm_mon and tm_mday to 1
        ev->date.tm_mon++;
        ev->date.tm_mday++;
        ev->date.tm_year += 1900;

        // Declare a new node and change it
        ev->next = new EventNode;
        ev = ev->next;

        count++;
    }
    return count;
}