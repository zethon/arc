#pragma once
#include <atomic>

#include <fmt/core.h>
#include <curses.h>

#include "StatusLine.h"

namespace arc
{

struct AppConfig
{

};

class App
{

public: 
    App();
    App(const AppConfig& config);
    ~App();

    void run();

private:
    void draw();
    void draw_menubar();
    void draw_statusbar();

    std::string getUserCommand();

    std::atomic_bool    _running = true;
    StatusLine          _statusline;
    bool                _showCommandPrompt = false;

    WINDOW* _mainWindow = nullptr;
};

} // namespace arc
