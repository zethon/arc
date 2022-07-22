#include <curses.h>

int main(void)
{   
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, false);
    start_color();
    use_default_colors();
    curs_set(0);
    
    WINDOW *pad = newpad(LINES+1, COLS);

    wprintw(pad, "Hello, World!\n");
    prefresh(pad, 0, 0, 0, 0, LINES-1, COLS);

    wgetch(pad);

    delwin(pad);
    endwin();
    return 0;
}