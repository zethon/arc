#include <fstream>
#include <functional>

#include <boost/algorithm/string.hpp>
#include <filesystem>

#include "NCursesUtils.h"
#include "ColorPairs.h"
#include "ArcUtils.h"
#include "ArcApp.h"

using namespace std::literals::string_literals;

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

    // hide the cursor
    curs_set(0);

    // application color pairs
    init_pair(CP_STATUS_BAR, COLOR_BLUE, COLOR_WHITE);
    init_pair(CP_URL_BAR, COLOR_BLUE, COLOR_WHITE);
    init_pair(CP_BG, COLOR_BLACK, COLOR_GREEN);

    init_commands();

    _canvas = std::make_unique<Canvas>(LINES-2, COLS, 1, 0);
    show("/Users/addy/src/arc/arc/ArcApp.cpp");
}

void App::init_commands()
{
    _actions.push_back({"quit"s, 
        "Quit the application"s, 
        [&](const std::string&) { _running = false; }});

    _actions.push_back({"go"s, 
        "Go"s, 
        [&](const std::string& url) { this->go(url); }});

    _actions.push_back({"show"s, 
        "Show"s, 
        [&](const std::string& filename)
        { 
            this->show(filename);
        }});

    _actions.push_back({"t"s, 
        "t"s, 
        [&](const std::string& url) { show("/Users/addy/src/arc/arc/ArcApp.cpp"); }});

}

void App::execute_command(const std::string& original)
{
    std::string command { original };
    boost::trim(command);
    if (command.empty()) return;

    std::vector<std::string> params;
    boost::split(params, command, boost::is_any_of(" "));
    if (params.empty()) return;

    auto actionIt = std::find_if(_actions.begin(), _actions.end(), 
        [&](const Action& action) { return action.name == params[0]; });

    if (actionIt != _actions.end())
    {
        params.erase(params.begin()); // remove the command name
        std::string paramstr = boost::join(params, " ");
        actionIt->action(paramstr);
    }
}

App::~App()
{
    endwin();
}

void App::go(const std::string& url)
{
    _urlbar.setLocation(url);
    ::utils::openBrowser(url);
    // wrefresh(_pageWindow);
}

void App::show(const std::string& filename)
{
    if (!std::filesystem::exists(filename))
    {
        const auto msg = fmt::format("File not found: {}", filename);
        utils::message_box(msg);
        return;
    }

    if (!std::filesystem::is_regular_file(filename))
    {
        const auto msg = fmt::format("{} cannot be displayed", filename);
        utils::message_box(msg);
        return;
    }

    const auto filesize = std::filesystem::file_size(filename);
    if (filesize > 1024 * 1024 * 10)
    {
        const auto msg = fmt::format("{} is too large to display", filename);
        utils::message_box(msg);
        return;
    }

    _urlbar.setLocation(filename);
    std::ifstream in(filename.data());
    _canvas->set_buffer(in);
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

            case '[':
                wscrl(_pageWindow, -1);
                wrefresh(_pageWindow);
            break;

            case ']':
                wscrl(_pageWindow, 1);
                wrefresh(_pageWindow);
            break;

            case '/':
            {
                const auto input = getUserCommand();
                execute_command(input);
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
    
    move(LINES-1, static_cast<int>(prompt.size()));
    const auto result = arc::utils::getUserInput(stdscr, 60);
    attroff(COLOR_PAIR(CP_STATUS_BAR));
    attron(A_REVERSE | A_BOLD);
    
    return result;
}

void App::draw()
{
    // we must refresh the top and bottom parts of the screen
    // before we draw the page
    _urlbar.draw();
    _statusline.draw();
    refresh();
    
    _canvas->draw();
}

void App::draw_menubar()
{
}

void App::draw_statusbar()
{

}

} // namespace arc
