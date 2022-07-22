#pragma once
#include <cstddef>

#include <ncurses.h>

namespace arc
{

class Canvas
{

public:
    Canvas(int y, int x, int height, int width);

    void set_buffer(char* buffer, std::size_t len);
    void set_buffer(std::istream& stream);

    void draw();

private:
    void delete_pad();

    int _y;
    int _x;
    int _height;
    int _width;

    WINDOW* _pad = nullptr;

};

} // namespace arc
