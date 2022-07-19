#include <curses.h>

#include <fmt/core.h>

#include "ColorPairs.h"
#include "UrlBar.h"

namespace arc
{

void UrlBar::draw()
{
    move(0, 0);
    attron(COLOR_PAIR(CP_URL_BAR));
    attron(A_REVERSE | A_BOLD);
    printw(fmt::format("{:<{}}", _location, COLS).data());
    attroff(COLOR_PAIR(CP_URL_BAR));
    attron(A_REVERSE | A_BOLD);
}

} // namespace arc
