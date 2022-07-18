#include <form.h>

#include "ArcUtils.h"
#include "ColorPairs.h"
#include "ArcApp.h"

namespace arc
{

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
    init_pair(CP_STATUS_BAR, COLOR_CYAN, -1);
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
    const auto result = arc::utils::getUserInput(stdscr);
    attroff(COLOR_PAIR(CP_STATUS_BAR));
    attron(A_REVERSE | A_BOLD);
    
    return result;
}

void App::draw()
{
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
