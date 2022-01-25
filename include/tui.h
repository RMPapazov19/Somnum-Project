#pragma once

#ifdef _WIN32
#include <PDcurses/curses.h>
#include <PDcurses/panel.h>
#else
#include <ncurses.h>
#include <panel.h>
#endif

#include "backend.h"

void updatePanels();
bool handleInput();

void initTUI(WINDOW *windows[3], PANEL *panels[3]);

void TUI(WINDOW *windows[3]);
