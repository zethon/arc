#include <fmt/core.h>

#include <curses.h>

#include "ColorPairs.h"
#include "StatusLine.h"

namespace arc
{   

StatusLine::StatusLine()
{
    initCommands();
}

void StatusLine::initCommands()
{
    _commands.emplace_back(Command{
        "Quit",
        "q",
        {},
        true
    });

    _commands.emplace_back(Command{
        "Help",
        "h",
        {},
        true
    });

    _commands.emplace_back(Command{
        "Prompt",
        "/",
        {},
        true
    });

    _commands.emplace_back(Command{
        "Login",
        "l",
        {},
        false
    });

    _commands.emplace_back(Command{
        "Refresh",
        "r",
        {},
        true
    });
}

std::string StatusLine::getStatusString()
{
    std::string retval;
    for(const auto& command : _commands)
    {
        if (command.enabled)
        {
            retval += fmt::format("[{}]{} ", command.hotkey, command.name);
        }
    }

    if (!retval.empty()) retval.pop_back();

    return fmt::format("{:<{}}", retval, COLS);
}

void StatusLine::draw()
{
    move(LINES-1, 0);
    attron(COLOR_PAIR(CP_STATUS_BAR));
    attron(A_REVERSE | A_BOLD);
    printw(getStatusString().c_str());
    attroff(COLOR_PAIR(CP_STATUS_BAR));
    attron(A_REVERSE | A_BOLD);
}

} // namespace arc
