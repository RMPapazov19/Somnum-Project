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
 * @brief Function to update all panels
 * 
 */
void updatePanels();

/**
 * @brief Function that initializes the TextUI
 * 
 * @param wins Array of all windows
 * @param panels Array of all windows
 */
void initTUI(WINDOW *windows[3], PANEL *panels[3]);

/**
 * @brief Main TextUI function
 * 
 * @param windows Array of all windows
 */
void TUI(WINDOW *windows[3]);