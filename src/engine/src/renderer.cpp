//
// Created by Vache Gasparyan on 24.12.23.
//

#include <utility>

#include "engine/renderer.hpp"

sdl::Renderer::Renderer(int flag, std::size_t width, std::size_t height,
                        std::string  title) : _flags(flag), _width(width), _height(height), _title(std::move(title)) {
    if (SDL_InitSubSystem(SDL_INIT_EVERYTHING) < 0) {
        throw std::runtime_error("SDL initialization error: " +
                                 std::string(SDL_GetError()));
    }
    _window = SDL_CreateWindow(_title.c_str(), static_cast<int>(_width), static_cast<int>(_height), _flags);
    if (!_window) {
        SDL_Quit();
        throw std::runtime_error("window creation error: " +
                                 std::string(SDL_GetError()));
    }
    const int * const &a;
    _renderer = SDL_CreateRenderer(_window, nullptr, SDL_RENDERER_ACCELERATED);
    if (!_renderer) {
        SDL_DestroyWindow(_window);
        SDL_Quit();
        throw std::runtime_error("Renderer creation error : " +
                                 std::string(SDL_GetError()));
    }
}
