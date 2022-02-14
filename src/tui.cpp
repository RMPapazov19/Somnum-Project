#include "tui.h"

/**
 * @brief Function to update panels
 *
 */
void updatePanels()
{
    update_panels();
    doupdate();
}

/**
 * @brief Create a popup window
 *
 * @return PANEL* Popoup window
 */
PANEL *createPopupWindow()
{
    // Define popup window and correcponding panel
    WINDOW *win;
    PANEL *pan;

    // Get the dimensions of the opened terminal
    int maxX, maxY;
    getmaxyx(stdscr, maxY, maxX);

    // Create a window with size of 8 x 28 and
    // place it in the middle of the screen
    win = newwin(8, 28, maxY / 4 + 4, maxX / 4 + 14);
    pan = new_panel(win);

    // Create a box around the window
    box(win, 0, 0);

    // Hide the panel
    hide_panel(pan);
    return pan;
}

/**
 * @brief Get user input needed to append event
 *
 * @param evName C string that holds name of event
 * @param evDate C string that holds date of event
 */
void getInput(char *evName, char *evDate)
{
    // Get the popup window
    WINDOW *win = panel_window(panel_below(NULL));

    // Print operation in the corner of window
    mvwprintw(win, 0, 1, " Add event ");

    // Print all options
    mvwprintw(win, 1, 1, "Name:");
    mvwprintw(win, 2, 1, "Date:");
    mvwprintw(win, 3, 1, "(YYYY-MM-DD) ");

    // Get input for all options
    wmove(win, 1, 6);
    mvwgetstr(win, 1, 6, evName);
    box(win, 0, 0);
    mvwprintw(win, 0, 1, " Add event ");
    wmove(win, 3, 14);
    mvwgetstr(win, 2, 7, evDate);

    // Clear popup window
    wclear(win);
    box(win, 0, 0);
}

/**
 * @brief Display help menu
 *
 */
void displayHelp()
{
    // Get the popup window
    WINDOW *win = panel_window(panel_below(NULL));

    // Display help menu with all keybinds
    mvwprintw(win, 0, 1, " Keybinds ");
    mvwprintw(win, 1, 1, "| Keybind | Action       |");
    mvwprintw(win, 2, 1, "--------------------------");
    mvwprintw(win, 3, 1, "|    a    | Add event    |");
    mvwprintw(win, 4, 1, "|    z    | Delete event |");
    mvwprintw(win, 5, 1, "|    w    | Go up        |");
    mvwprintw(win, 6, 1, "|    s    | Go down      |");

    // Update panels and wait for input
    updatePanels();
    getch();

    // Clean up popup window
    wclear(win);
    box(win, 0, 0);
}

/**
 * @brief Function that handles input
 *
 * @param ev Event node
 * @param popup Popup windwow
 * @param highlight Index of selected event
 * @param maxEvents Number of max events
 */
void handleInput(EventNode *ev, PANEL *popup, short &highlight, short &maxEvents)
{

    switch (getch())
    {
    // Quit porgram
    case 'q':
        curs_set(1);
        echo();
        exit(0);
        break;

    // Move up an event
    case 'w':
        highlight--;
        break;

    // Move down an event
    case 's':
        highlight++;
        break;

    // Append a node
    case 'a':
        // Show the popup window and append a node
        show_panel(popup);
        echo();

        char name[80];
        char date[20];

        getInput(name, date);
        appendNodeToFile(name, date);
        maxEvents++;

        // Update the linked list and hide the popup panel
        updateEventList(ev);

        noecho();
        hide_panel(popup);
        break;

    // Delete a selected event
    case 'z':
        if(highlight >= 1)
        {
            // and the collumns of the data file may be deleted
            deleteNodeAtIndex(highlight);
            maxEvents--;

            // Update event list
            updateEventList(ev);
        }
        break;

    // Display help menu
    case 'h':
        // Show popup panel, display help menu
        // and hide panel again
        show_panel(popup);
        displayHelp();
        hide_panel(popup);
        break;
    }

    // If highlight goes over maxEvents
    // set it to maxEvents
    if (highlight > maxEvents-1 && highlight != 0)
    {
        highlight = maxEvents-1;
    }
    // If highlight is less than the minimum event
    // set it to minimum event
    if (highlight < 0)
    {
        highlight = 0;
    }
}

/**
 * @brief Print all events from event linked list
 *
 * @param wins Array of all windows
 * @param ev Event node
 * @param highlight Index of selected element
 */
void printEventList(WINDOW *wins[3], EventNode *ev, const short highlight)
{
    // Short coresponding to current event
    short current = 1;
    ev = ev->next;

    // Max characters of timeline
    int maxTimelineChars = 1;  

    // Printing timeline
    for (int i = 2; i < getmaxx(wins[0]) - 3; i++)
    {
        maxTimelineChars += 1;
        mvwprintw(wins[0], 1, i, "-");
    }
    // Add the ending arrow
    mvwprintw(wins[0], 1, getmaxx(wins[0]) - 3, ">");

    // Printing events and putting marks on the timeline
    while (ev != NULL)
    {
        // If highlight == current then highlight text
        if (highlight+1 == current)
        {
            // Highlight text on wins[1]
            wattron(wins[1], A_STANDOUT);
            mvwprintw(wins[1], current, 1, "%s - %i-%i-%i",
                      ev->name.c_str(),
                      ev->date.tm_year,
                      ev->date.tm_mon,
                      ev->date.tm_mday);
            wattroff(wins[1], A_STANDOUT);

            // Clear description windwow and print event selected event description
            wclear(wins[2]);
            box(wins[2], 0, 0);
            mvwprintw(wins[2], 0, 1, " Description ");
            mvwprintw(wins[2], 1, 1, "%s", ev->desc.c_str());
        }
        else
        {
            mvwprintw(wins[1], current, 1, "%s - %i-%i-%i",
                      ev->name.c_str(),
                      ev->date.tm_year,
                      ev->date.tm_mon,
                      ev->date.tm_mday);
        }

        // Calculate the position of the mark and display it
        double timelinePosX = (ev->date.tm_year * maxTimelineChars) / 2022;
        mvwaddch(wins[0], 1, timelinePosX, '|');

        current++;
        ev = ev->next;
    }
}

/**
 * @brief Function to initialize the TUI
 *
 * @param wins Array of all windows
 * @param panels Array of all panels
 */
void initTUI(WINDOW *wins[3], PANEL *panels[3])
{
    // Turn off displaying of characters to screen
    noecho();

    // Turn off cursor
    curs_set(0);

    // Timeline window
    wins[0] = newwin(3, getmaxx(stdscr), 0, 0);

    // Events window
    wins[1] = newwin(getmaxy(stdscr) - 3, 30, 3, 0);

    // Description window
    wins[2] = newwin(getmaxy(stdscr) - 3, getmaxx(stdscr) - 30, 3, 30);

    // Create a box around all windows
    for (int i = 0; i < 3; ++i)
    {
        box(wins[i], 0, 0);
    }

    // Create a panel for each window
    for (int i = 0; i < 3; ++i)
    {
        panels[i] = new_panel(wins[i]);
    }

    // Print heading for each window
    mvwprintw(wins[0], 0, 1, " Timeline ");
    mvwprintw(wins[1], 0, 1, " Events ");
    mvwprintw(wins[2], 0, 1, " Event description ");
}

/**
 * @brief Main loop of TUI application
 *
 * @param windows Array of all windows on the screen
 */
void TUI(WINDOW *windows[3])
{
    // Create head of linked list containing EventNode
    EventNode *head = new EventNode;
    // Declare and initialize highlight
    short highlight = 0;
    short maxEvents;

    // Create popup window
    PANEL *popup = createPopupWindow();

    // Initialize event list
    maxEvents = updateEventList(head);
    sortList(&head);

    while (true)
    {
        // Clear "Events" window
        wclear(windows[1]);
        box(windows[1], 0, 0);
        mvwprintw(windows[1], 0, 1, " Events ");
        // Print event list and update panels
        sortList(&head);
        printEventList(windows, head, highlight);
        updatePanels();
        // Wait for input
        handleInput(head, popup, highlight, maxEvents);
    }
}