//
// Created by Vache Gasparyan on 04.01.24.
//

#include "engine/window.hpp"

#include <cassert>
#include <string>

namespace sdl {

Window::Window(std::string_view title, size_t width, size_t height, int flag)
    : _flags(flag), _width(width), _height(height), _title(title) {
    if (SDL_InitSubSystem(SDL_INIT_EVERYTHING) < 0) {
        throw std::runtime_error("SDL initialization error: " +
                                 std::string(SDL_GetError()));
    }
    _window.reset(SDL_CreateWindow(_title.data(), static_cast<int>(_width),
                                   static_cast<int>(_height), _flags));
    if (!_window) {
        SDL_Quit();
        throw std::runtime_error("window creation error: " +
                                 std::string(SDL_GetError()));
    }
    _renderer = std::make_shared<Renderer>(*this);
}

const std::unique_ptr<SDL_Window, sdlWindowDeleter>& Window::window() const {
    return _window;
}

int Window::flags() const noexcept {
    return _flags;
}

std::size_t Window::width() const noexcept {
    return _width;
}

std::size_t Window::height() const noexcept {
    return _height;
}

const std::string_view& Window::title() const {
    return _title;
}

const std::shared_ptr<Renderer>& Window::renderer() const {
    return _renderer;
}

Window::~Window() {
    _renderer.reset();
    assert(_renderer.use_count() == 0);
}
}  // namespace sdl