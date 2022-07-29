#pragma once
#include <cstddef>
#include <any>

#include <ncurses.h>

namespace arc
{

constexpr auto MSG_KEYUP = 1u;
constexpr auto MSG_KEYDOWN = 2u;
constexpr auto MSG_KEYLEFT = 3u;
constexpr auto MSG_KEYRIGHT = 4u;

class Canvas
{

public:
    Canvas(int y, int x, int height, int width);

    void set_buffer(char* buffer, std::size_t len);
    void set_buffer(std::istream& stream);
    void set_buffer(std::string_view str);

    void draw();

    void send_message(std::uint32_t message, const std::any& data);

private:
    void delete_pad();

    int _y;
    int _x;
    int _height;
    int _width;

    WINDOW* _pad = nullptr;

};

} // namespace arc
