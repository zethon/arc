#pragma once
#include <curses.h>
#include <string>

namespace arc::utils
{

inline std::string getUserInput(WINDOW* win = stdscr)
{
    std::string retval;
    int x = 0, y=0;

    while (true)
    {
        getyx(win, y, x);

        int ch = getch();
        if (ch == '\n' || ch == -1)
        {
            break;
        }
        else if (ch == '\b' || ch == 127 || ch == KEY_BACKSPACE)
        {
            if (!retval.empty())
            {
                mvaddch(y, x-1, ' ');
                move(y, x-1);
                retval.pop_back();
            }
        }
        else if (ch == 27)
        {
            retval.clear();
            break;
        }
        else
        {
            retval += ch;
            mvaddch(y, x, ch);
        }
    }

    return retval;
}

inline void rectangle(int y1, int x1, int y2, int x2)
{
    mvhline(y1, x1, 0, x2-x1);
    mvhline(y2, x1, 0, x2-x1);
    mvvline(y1, x1, 0, y2-y1);
    mvvline(y1, x2, 0, y2-y1);
    mvaddch(y1, x1, ACS_ULCORNER);
    mvaddch(y2, x1, ACS_LLCORNER);
    mvaddch(y1, x2, ACS_URCORNER);
    mvaddch(y2, x2, ACS_LRCORNER);
}

} // namespace arc::utils
