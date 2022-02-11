#pragma once

#include "backend.h"

// Preprocessor macro to include correct
// libraries based on operating system
#ifdef _WIN32
#include <PDcurses/curses.h>
#include <PDcurses/panel.h>
#else
#include <ncurses.h>
#include <panel.h>
#endif

/**
 * @brief Function to initialize the TUI
 *
 * @param wins Array of all windows
 * @param panels Array of all panels
 */
void initTUI(WINDOW *windows[3], PANEL *panels[3]);

/**
 * @brief Main loop of TUI application
 *
 * @param windows Array of all windows on the screen
 */
void TUI(WINDOW *windows[3]);