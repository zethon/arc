#include <streambuf>
#include <istream>
#include <string>
#include <iostream>

#include "ColorPairs.h"
#include "Canvas.h"

namespace arc
{

struct MemoryBuffer : std::streambuf 
{
    MemoryBuffer(char* base, std::ptrdiff_t n) 
    {
        this->setg(base, base, base + n);
    }
};

std::size_t line_count(std::streambuf& buffer)
{
    std::istream in(&buffer);

    std::size_t count = 0;
    std::string line;
    while (std::getline(in, line))
    {
        ++count;
    }

    return count;
}

Canvas::Canvas(int y, int x, int height, int width)
    : _y(y), _x(x), _height(height), _width(width)
{
    
}

void Canvas::set_buffer(char* buffer, std::size_t len)
{
    MemoryBuffer membuf(buffer, len);
    int lcount = line_count(membuf);

    delete_pad();
    _pad = newpad (LINES+1, COLS);
    wprintw(_pad, "Hello, World!\n");

    // std::istream in(&membuf);
    // std::string line;
    // while (std::getline(in, line))
    // {
    //     wprintw(_pad, "%s\n", line.data()); 
    // }

    prefresh(_pad, 0, 0, 0, 0, LINES-1, COLS);
}

void Canvas::set_buffer(std::istream& stream)
{
    delete_pad();

    // _pad = newpad(LINES+10, COLS);
    // wprintw(_pad, "Hello, World!\n");

    _pad = newpad(LINES+10, COLS);
    // wprintw(_pad, "Hello, World!\n");
    // prefresh(_pad, 0, 0, 0, 0, LINES-1, COLS);

    // std::istream in(&membuf);
    std::string line;
    while (std::getline(stream, line))
    {
        wprintw(_pad, "%s\n", line.data()); 
    }

    // prefresh(_pad, 0, 0, 0, 0, LINES-1, COLS);
}

void Canvas::draw()
{

    prefresh(_pad, 0, 0, 1, 0, LINES-2, COLS);
    // wgetch(pad);
}

void Canvas::delete_pad()
{
    if (_pad)
    {
        delwin(_pad);
        _pad = nullptr;
    }
}

} // namespace arc
