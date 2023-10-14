#pragma once

#include <SDL.h>
#include <string>
#include "color.hpp"

namespace sdl {

class Engine {
public:
    void init(const std::string& title, size_t width, size_t height, int flags);
    void pollEvents();

    static Engine& getInstance();

    void clear();
    void present();

    size_t width() const;
    size_t height() const;
    void setDrawColor(Color color);

private:
    Engine() = default;
    ~Engine();
    Engine(const Engine&) = delete;
    Engine& operator=(const Engine&) = delete;

private:
    SDL_Window* _window;
    SDL_Renderer* _renderer;
    size_t _width;
    size_t _height;

private:
    static bool _initialized;
};

}  // namespace sdl