#pragma once

#include <cstddef>

#include <curses.h>

namespace arc
{

class Canvas;
using CanvasPtr = std::weak_ptr<Canvas>;

class Renderer;
using RendererPtr = std::unique_ptr<Renderer>;

class TextRenderer;
using TextRendererPtr = std::unique_ptr<TextRenderer>;

class Renderer
{
public:
    Renderer(CanvasPtr canvas)
        : _canvas(canvas)
    {
        // nothing to do
    }

    virtual void draw(WINDOW*, const char* buffer, std::size_t len) = 0;

private:
    CanvasPtr _canvas;
};

class TextRenderer : public Renderer
{

public:
    void draw(WINDOW*, const char* buffer, std::size_t len) override;
};

class HtmlRenderer : public Renderer
{

public:
    void draw(WINDOW*, const char* buffer, std::size_t len) override;
};

} // namespace arc
