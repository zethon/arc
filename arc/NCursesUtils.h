#pragma once
#include <curses.h>
#include <string>

namespace arc::utils
{

inline std::string getUserInput(WINDOW* win, std::size_t maxlen = 0, char echo = '\0')
{
    std::string retval;
    int x = 0, y=0;

    curs_set(1);

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
        else if (maxlen == 0 || retval.size() < maxlen)
        {
            retval += ch;
            if (echo != '\0') ch = echo;
            mvaddch(y, x, ch);
        }
    }

    curs_set(0);
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

static void message_box(std::string_view msg)
{
    int row = 0, col = 0;
    getmaxyx(stdscr, row, col);
    row = row / 2;
    col = (col - msg.size()) / 2;
    utils::rectangle(row - 1, col - 1, row + 1, col + msg.size());
    mvprintw(row, col, msg.data());
    getch();
    move(row-1, 0);
    clrtoeol();
    move(row, 0);
    clrtoeol();
    move(row+1, 0);
    clrtoeol();
}

static void fill_window(WINDOW *win, chtype ch)
{
    int y, x;
    int y0, x0;
    int y1, x1;

    getyx(win, y0, x0);
    getmaxyx(win, y1, x1);
    for (y = 0; y < y1; ++y) {
	for (x = 0; x < x1; ++x) {
	    mvwaddch(win, y, x, ch);
	}
    }
    wsyncdown(win);
    wmove(win, y0, x0);
    wrefresh(win);
}

} // namespace arc::utils
