#include <curses.h>

int main(void)
{   
    initscr();
    WINDOW *pad = newpad(LINES+1, COLS);

    wprintw(pad, "Hello, World!\n");
    prefresh(pad, 0, 0, 0, 0, LINES-1, COLS);

    wgetch(pad);

    delwin(pad);
    endwin();
    return 0;
}