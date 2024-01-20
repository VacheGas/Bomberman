#pragma once

#include "graphic_element.hpp"
#include "sprite.hpp"
#include "vec.hpp"

#include <string>
#include "SDL3/SDL.h"

#include <memory>
#include <unordered_map>
#include <vector>

namespace sdl {

class Engine {
public:
    Engine(std::string_view, size_t width, size_t height, int flags);
    Engine(const Engine&) = delete;
    Engine& operator=(const Engine&) = delete;
    ~Engine();

    void run();

    std::size_t registerGraphicElement(std::string_view assetPath,
                                       Vec4 dstRect);

    std::size_t width() const;
    std::size_t height() const;
    void setDrawColor(SDL_Color color);

private:
    Texture load(const std::string& assetPath);
    void present();
    void update();
    void clear();
    void draw(SDL_Renderer* renderer);

private:
    void initSDL();
    void cleanSDL();

private:
    std::string_view _title;
    size_t _width;
    size_t _height;
    int _flags;
    SDL_Window* _window;
    SDL_Renderer* _renderer;
    std::unordered_map<std::size_t, std::unique_ptr<GraphicElement>>
        _graphicElements{};
    std::unique_ptr<SpriteFactory> _factory{std::make_unique<SpriteFactory>()};

private:
    static bool _initialized;
};

}  // namespace sdl