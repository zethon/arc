#include <fstream>
#include <functional>
#include <filesystem>
#include <regex>

#include <boost/algorithm/string.hpp>
#include <boost/url/src.hpp>

#include <md4c.h>

#include "home_md.h"
#include "about_md.h"
#include "help_md.h"

#include "NCursesUtils.h"
#include "ColorPairs.h"
#include "ArcUtils.h"
#include "ArcApp.h"
#include "Renderer.h"

using namespace std::literals::string_literals;
using namespace std::literals::string_view_literals;

namespace arc
{

const static std::map<std::string_view, const char*> STATIC_PAGES_MAP =
{
    { "home", &(home_md[0]) },
    { "about"sv, &(about_md[0]) },
    { "help"sv, &(help_md[0]) },
};

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
    // _renders.emplace(RenderType::Text, std::make_unique<TextRenderer>());

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

    
    // _canvas->setRenderer(textRenderer);
    // _canvas->draw()

    _canvas = std::make_unique<Canvas>(LINES-2, COLS, 1, 0);
    // _canvas->set_buffer(const_cast<char*>(&home_md[0]), strlen(home_md));

    // MD_PARSER mdparser;
    // mdparser.flags = 1;

    // std::string_view test = "# Hi there!";

    // auto x = md_parse(test.data(), test.size(), &mdparser, nullptr);
    // std::cout << "x: " << x << std::endl;

    go("arc://home"s);
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
    else
    { 
        go(original);
    }
}

App::~App()
{
    endwin();
}

void App::go(const std::string& url)
{
    namespace bu = boost::urls;

    const static std::regex domain_regex("^(?!-)[A-Za-z0-9-]+([\\-\\.]{1}[a-z0-9]+)*\\.[A-Za-z]{2,6}$");

    bu::string_view urlsv{url};
    const auto result = bu::parse_uri(urlsv);

    if (result.has_value())
    {
        const auto& uri = result.value();
        if (uri.scheme() == "arc")
        {
            auto it = STATIC_PAGES_MAP.find(uri.host().to_string());
            if (it != STATIC_PAGES_MAP.end())
            {
                _canvas->set_buffer(const_cast<char*>(it->second), strlen(it->second));
            }
        }
        else if (uri.scheme() == "file")
        {
            // std::filesystem::path path(uri.encoded_path().to_string());
            // if (std::filesystem::exists(path))
            // {
            //     std::ifstream ifs(path);
            //     std::string content((std::istreambuf_iterator<char>(ifs)),
            //                         (std::istreambuf_iterator<char>()));

            //     _canvas->set_buffer(const_cast<char*>(content.c_str()), content.size());
            // }
            // else
            // {
            //     arc::utils::message_box(fmt::format("file '{}' not found", path.string()));
            // }
        }

        _urlbar.setLocation(url);
    }
    else if (auto it = STATIC_PAGES_MAP.find(url); it != STATIC_PAGES_MAP.end())
    {
        // this was not a valid URL, so first we look for an internal page
        // by the name of what was typed, and then if that doesn't exist
        // we see if this looks like a domain name, and if so try to load that
        // otherwise popup an error
        _canvas->set_buffer(const_cast<char*>(it->second), strlen(it->second));
        bu::url dest;
        dest.set_host(url);
        dest.set_scheme("arc");
        _urlbar.setLocation(std::string{dest.string()});
    }
    else if(std::regex_match(url, domain_regex))
    {
        bu::url dest;
        dest.set_host(url);
        dest.set_scheme("https");
        _urlbar.setLocation(std::string{dest.string()});

        ::utils::openBrowser(std::string{dest.string()});
    }
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

} // namespace arc
