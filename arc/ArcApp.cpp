#include <fstream>

#include <form.h>

#include "ArcUtils.h"
#include "ColorPairs.h"
#include "ArcApp.h"

namespace arc
{

namespace
{

WINDOW *create_newwin(int height, int width, int starty, int startx)
{
    WINDOW *local_win;

    local_win = newwin(height, width, starty, startx);

    wrefresh(local_win);
    refresh();

    return local_win;
}

} // namespace anonymous

App::App()
    : App(AppConfig{})
{
}

App::App(const AppConfig& config)
{
    _mainWindow = initscr();
    noecho();
    cbreak();
    keypad(stdscr, false);
    start_color();
    use_default_colors();

    // application color pairs
    init_pair(CP_STATUS_BAR, COLOR_BLUE, COLOR_WHITE);
    init_pair(CP_URL_BAR, COLOR_BLUE, COLOR_WHITE);
    init_pair(CP_BG, COLOR_BLACK, COLOR_GREEN);

    _pageWindow = create_newwin(LINES-2, COLS, 1, 0);
  
    go("file://Users/addy/src/arc/arc/ColorPairs.h");
}

App::~App()
{
    endwin();
}

void App::go(const std::string& url)
{
    _urlbar.setLocation(url);

    std::ifstream myfile("/Users/addy/src/arc/arc/ArcApp.cpp");
    std::string line;

    while (std::getline(myfile, line))
    {
        waddstr(_pageWindow, line.c_str());
    }

    wrefresh(_pageWindow);
}

void App::run()
{
    while (_running)
    {
        draw();

        const auto key = getch();
        switch (key)
        {
            default:
            break;

            case 'q':
                _running = false;
            break;

            case '/':
            {
                const auto input = getUserCommand();
                move(0,0);
                printw(fmt::format("You typed: [{}]", input).c_str());
            }
            break;
        }
    }
}

std::string App::getUserCommand()
{
    attron(COLOR_PAIR(CP_STATUS_BAR));
    attron(A_REVERSE | A_BOLD);

    const std::string prompt = "> ";
    const auto statusline = fmt::format("{:<{}}", prompt , COLS);
    move(LINES-1, 0);
    printw(statusline.data());
    
    move(LINES-1, prompt.size());
    const auto result = arc::utils::getUserInput(stdscr, 60);
    attroff(COLOR_PAIR(CP_STATUS_BAR));
    attron(A_REVERSE | A_BOLD);
    
    return result;
}

void App::draw()
{
    wmove(stdscr, 20, 20);
    waddstr(stdscr, "Hello World!");
    
    wbkgd(_pageWindow, COLOR_PAIR(CP_BG));
    wmove(_pageWindow, 0, 0);
    wprintw(_pageWindow, "Hello World1!");

    _urlbar.draw();
    _statusline.draw();
    refresh();
}

void App::draw_menubar()
{

}

void App::draw_statusbar()
{

}

} // namespace arc
