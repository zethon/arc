#pragma once
#include <atomic>

#include <fmt/core.h>
#include <curses.h>

#include "StatusLine.h"
#include "UrlBar.h"

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
    void go(const std::string& url);

private:
    void draw();
    void draw_menubar();
    void draw_statusbar();

    std::string getUserCommand();

    std::atomic_bool    _running = true;
    bool                _showCommandPrompt = false;

    WINDOW* _mainWindow = nullptr;
    WINDOW* _pageWindow = nullptr;

    StatusLine          _statusline;
    UrlBar              _urlbar;
};

} // namespace arc
