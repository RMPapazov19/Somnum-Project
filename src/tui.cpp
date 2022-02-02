#include "tui.h"

/**
 * @brief Function to update all panels
 * 
 */
void updatePanels()
{
    update_panels();
    doupdate();
}

/**
 * @brief Create a Popup Window and hide it
 * 
 * @return PANEL* Returns the hidden popup panel
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
 * @brief Display help table with all keybinds
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
 * @brief Function that handels input
 * 
 * @param highlight Highlighted option in events panel
 * @param ev Event list
 * @param popup Popup window where all will be printed
 */
void handleInput(short &highlight, EventNode *ev, PANEL *popup, WINDOW *win)
{
    switch (getch())
    {
    // Quit porgram
    case 'q':
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
        appendNode();

        // Update the linked list and hide the popup panel
        updateEventList(ev);
        hide_panel(popup);
        break;

    // Delete a selected event
    case 'z':
        deleteNodeAtIndex(highlight);
        
        // Clear events window
        wclear(win);
        box(win, 0, 0);
        mvwprintw(win, 0, 1, " Events ");

        // Update event list
        updateEventList(ev);
        break;
    case 'h':
        // Show popup panel, display help menu
        // and hide panel again
        show_panel(popup);
        displayHelp();
        hide_panel(popup);
        break;
    }
    // If highlight is less than the minimum event
    // set it to minimum event
    if (highlight < 1)
    {
        highlight = 1;
    }
}

/**
 * \brief Function to print all event names and dates to
 *        the Events panel and selected event description
 * 
 * @param wins Array of all windows
 * @param ev Linked list of events to be printed on screen
 * @param highlight Option to be highlighted on screen
 */
void printEventList(WINDOW *wins[3], EventNode *ev, const short highlight)
{
    // Short coresponding to current event
    short current = 1;
    while (ev->next != nullptr)
    {
        // If highlight == current then highlight text
        if (highlight == current)
        {
            // Highlight text on wins[1]
            wattron(wins[1], A_STANDOUT);
            mvwprintw(wins[1], current, 1, "%s - %i.%i.%i", ev->name.c_str(), ev->day, ev->month, ev->year);
            wattroff(wins[1], A_STANDOUT);

            // Clear description windwow and print event selected event description
            wclear(wins[2]);
            box(wins[2], 0, 0);
            mvwprintw(wins[2], 0, 1, " Description ");
            mvwprintw(wins[2], 1, 1, "%s", ev->desc.c_str());
        }
        else
        {
            mvwprintw(wins[1], current, 1, "%s - %i.%i.%i", ev->name.c_str(), ev->day, ev->month, ev->year);
        }
        current++;
        ev = ev->next;
    }
}

/**
 * @brief Function that initializes the TextUI
 * 
 * @param wins Array of all windows
 * @param panels Array of all windows
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
 * @brief Main TextUI function
 * 
 * @param windows Array of all windows
 */
void TUI(WINDOW *windows[3])
{
    // Create head of linked list containing EventNode
    EventNode *head = new EventNode;

    // Create popup window
    PANEL *popup = createPopupWindow();

    // Initialize event list
    updateEventList(head);

    // Declare and initialize highlight
    short highlight = 1;
    while (true)
    {
        // Print event list and update panels
        printEventList(windows, head, highlight);
        updatePanels();

        // Wait for input
        handleInput(highlight, head, popup, windows[1]);
    }
}