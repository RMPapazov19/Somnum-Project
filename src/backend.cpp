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
    unsigned day, month;
    int year;

    // Print operation in the corner of window
    mvwprintw(win, 0, 1, " Add event ");

    // Print all options
    mvwprintw(win, 1, 1, "Name:");
    mvwprintw(win, 2, 1, "Day (Number):");
    mvwprintw(win, 3, 1, "Month (Number):");
    mvwprintw(win, 4, 1, "Year (Number):");

    // Get input for all options
    mvwgetstr(win, 1, 6, name);
    box(win, 0, 0);
    mvwprintw(win, 0, 1, " Add event ");
    mvwscanw(win, 2, 16, "%u", &day);
    box(win, 0, 0);
    mvwprintw(win, 0, 1, " Add event ");
    mvwscanw(win, 3, 18, "%u", &month);
    box(win, 0, 0);
    mvwprintw(win, 0, 1, " Add event ");
    mvwscanw(win, 4, 17, "%i", &year);

    // Clear popup window
    wclear(win);
    box(win, 0, 0);

    // Write event data to data file
    std::fstream data;
    data.open("data.csv", std::ios::app);
    data << name << "," << day << "," << month << "," << year << ","
         << "\"Edit me to add description\",\n";

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
void updateEventList(EventNode *ev)
{
    // Declare input stream and file stream 
    std::fstream data;
    std::ifstream fileTest;

    // Try to open data file
    fileTest.open("data.csv");

    // If data file can't be opened then it doesn't exist
    if (!fileTest)
    {
        // Create a data file
        data.open("data.csv", std::ios::in | std::ios::app);
        
        // Add columns for data
        data << "Name,Day,Month,Year,Desc,";
        data << "\n";

        // Close the file
        data.close();
    }

    // Create an object of type CSVReader and give it the csv data file
    io::CSVReader<5> in("data.csv");

    // Pass it columns where data will be stored
    in.read_header(io::ignore_extra_column, "Name", "Day", "Month", "Year", "Desc");
    
    // Read from file until data is present
    while (in.read_row(ev->name, ev->day, ev->month, ev->year, ev->desc))
    {
        // When all data has been placed in current node
        // Place data in next node
        ev->next = new EventNode;
        ev = ev->next;
    }
}