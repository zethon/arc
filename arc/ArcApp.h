#pragma once
#include <atomic>

#include <curses.h>

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

    std::atomic_bool _running = true;

};

} // namespace arc
