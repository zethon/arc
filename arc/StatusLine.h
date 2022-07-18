#pragma once
#include <vector>

namespace arc
{

struct Command
{
    
    std::string name;
    std::string hotkey;
    
    std::function<void()> action;
    bool enabled = true;
};


class StatusLine
{

public:
    StatusLine();

    void draw();

private:
    void initCommands();
    std::string getStatusString();

    std::vector<Command>    _commands;
};

} // namespace arc

