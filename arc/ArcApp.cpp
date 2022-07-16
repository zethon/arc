#include "ArcApp.h"

namespace arc
{

namespace
{

void rectangle(int y1, int x1, int y2, int x2)
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

} // namespace anonymous    

App::App()
    : App(AppConfig{})
{
    // initscr();
    cbreak();
    // noecho();
    // keypad(stdscr, true);
    // curs_set(0);
    // refresh();
}

App::App(const AppConfig& config)
{
    initscr();
}

App::~App()
{
    endwin();
}

void App::run()
{
    while (_running)
    {
        draw();
        auto key = getch();
        if (key == 'q')
        {
            _running = false;
        }
    }
}

void App::draw()
{
    rectangle(0, 0, LINES-1, COLS-1);
    printw("Hello World !!!");
    refresh();
}

void App::draw_menubar()
{

}

void App::draw_statusbar()
{

}

} // namespace arc
