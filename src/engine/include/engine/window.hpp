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
    static std::unique_ptr<Window> createWindow(int flag, size_t width, size_t height, std::string_view title);

   public:
    const std::unique_ptr<SDL_Window, sdlWindowDeleter>&  window() const;
    int flags() const;
    size_t width() const;
    size_t height() const;
    const std::string_view& title() const;

   private:
    Window() = default;
    Window(int flag, size_t width, size_t height, std::string_view title);
   private:
    int _flags{};
    std::size_t _width{};
    std::size_t _height{};
    std::unique_ptr<SDL_Window, sdlWindowDeleter> _window = nullptr;
    std::string_view _title;
};

}  // namespace sdl
