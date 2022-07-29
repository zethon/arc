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

std::size_t line_count(char* input, std::size_t len)
{
    MemoryBuffer membuf(input, len);
    std::istream in(&membuf);

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

void Canvas::set_buffer(std::string_view str)
{
    set_buffer(const_cast<char*>(str.data()), str.size());
}

void Canvas::set_buffer(char* buffer, std::size_t len)
{
    int lcount = line_count(buffer, len);

    delete_pad();
    _pad = newpad(LINES+10, COLS);
    
    MemoryBuffer membuf(buffer, len);
    std::istream in(&membuf);

    set_buffer(in);
}

void Canvas::set_buffer(std::istream& stream)
{
    delete_pad();

    _pad = newpad(LINES+10, COLS);

    std::string line;
    while (std::getline(stream, line))
    {
        wprintw(_pad, "%s\n", line.data()); 
    }
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

void Canvas::send_message(std::uint32_t message, const std::any& data)
{

}

} // namespace arc
