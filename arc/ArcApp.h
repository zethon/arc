#pragma once
#include <atomic>

#include <fmt/core.h>
#include <curses.h>

#include "StatusLine.h"
#include "UrlBar.h"
#include "Canvas.h"
#include "Renderer.h"

namespace arc
{

enum class RenderType
{
    Text,
    Markdown,
    HTML
};

using RenderMap = std::map<RenderType, RendererPtr>;

struct AppConfig
{

};

struct Action
{
    std::string name;
    std::string description;
    std::function<void(const std::string&)> action;
};

class App
{

public: 
    App();
    App(const AppConfig& config);
    ~App();

    void run();
    void go(const std::string& url);
    void show(const std::string& filename);

private:
    void draw();
    void init_commands();
    void execute_command(const std::string& command);

    std::string getUserCommand();

    std::atomic_bool        _running = true;
    bool                    _showCommandPrompt = false;
    std::vector<Action>     _actions;

    WINDOW* _mainWindow = nullptr;
    WINDOW* _pageWindow = nullptr;

    std::unique_ptr<Canvas> _canvas;
    // RenderMap               _renders;

    StatusLine          _statusline;
    UrlBar              _urlbar;
    
};

} // namespace arc
