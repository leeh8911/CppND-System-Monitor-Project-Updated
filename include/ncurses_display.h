/* Copyright */
#ifndef NCURSES_DISPLAY_H
#define NCURSES_DISPLAY_H

#include <curses.h>

#include <string>
#include <vector>

#include "./process.h"
#include "./system.h"

namespace NCursesDisplay {
void Display(System& system, int16_t n = 10);
void DisplaySystem(System& system, WINDOW* window);
void DisplayProcesses(std::vector<Process>& processes, WINDOW* window,
                      int16_t n);
std::string ProgressBar(float percent);
};  // namespace NCursesDisplay

#endif  // NCURSES_DISPLAY_H