#pragma once

#ifdef _WIN32
#include <curses.h>
#include <panel.h>
#else
#include <ncurses.h>
#include <panel.h>
#endif

void updatePanels();
bool handleInput();

void initTUI(WINDOW *windows[3], PANEL *panels[3]);

void TUI(WINDOW *windows[3]);
