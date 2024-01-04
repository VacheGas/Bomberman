//
// Created by Vache Gasparyan on 04.01.24.
//

#include "engine/window.hpp"

#include <string>

namespace sdl {

Window::Window(int flag, size_t width, size_t height, std::string_view title)
    : _flags(flag), _width(width), _height(height), _title(title) {
    if (SDL_InitSubSystem(SDL_INIT_EVERYTHING) < 0) {
        throw std::runtime_error("SDL initialization error: " +
                                 std::string(SDL_GetError()));
    }
    _window.reset(SDL_CreateWindow(_title.data(), static_cast<int>(_width), static_cast<int>(_height), _flags));
    if (!_window) {
        SDL_Quit();
        throw std::runtime_error("window creation error: " +
                                 std::string(SDL_GetError()));
    }

}
const std::unique_ptr<SDL_Window, sdlWindowDeleter>& Window::window() const {
    return _window;
}
}  // namespace sdl