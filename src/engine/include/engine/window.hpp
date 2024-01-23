//
// Created by Vache Gasparyan on 04.01.24.
//

#pragma once

#include <SDL3/SDL.h>

#include "renderer.hpp"
#include "sdlWindowDeleter.hpp"

#include <memory>
#include <string_view>

namespace sdl {

class Window {
public:
    static std::unique_ptr<Window> createWindow(std::string_view title,
                                                size_t width, size_t height,
                                                int flag);

public:
    const std::unique_ptr<SDL_Window, sdlWindowDeleter>& window() const;
    int flags() const;
    std::size_t width() const;
    std::size_t height() const;
    const std::string_view& title() const;

private:
    Window(std::string_view title, size_t width, size_t height, int flag);

private:
    int _flags{};
    std::size_t _width{};
    std::size_t _height{};
    std::unique_ptr<SDL_Window, sdlWindowDeleter> _window = nullptr;
    std::string_view _title;
};

}  // namespace sdl
