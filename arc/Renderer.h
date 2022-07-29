#pragma once

#include <cstddef>

#include <curses.h>

namespace arc
{

class Renderer
{
public:
    virtual void draw(WINDOW*, const char* buffer, std::size_t len) = 0;
};

class TextRenderer : public Renderer
{

public:
    void draw(WINDOW*, const char* buffer, std::size_t len)
    {
        
    }
};

} // namespace arc
