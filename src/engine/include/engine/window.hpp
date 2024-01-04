//
// Created by Vache Gasparyan on 04.01.24.
//

#ifndef BOMBERMAN_WINDOW_HPP
#define BOMBERMAN_WINDOW_HPP

#include <SDL3/SDL.h>

#include "sdlWindowDeleter.hpp"

#include <memory>
#include <string_view>

namespace sdl {

class Window {
   public:
    Window() = default;
    Window(int flag, size_t width, size_t height, std::string_view title);
    const std::unique_ptr<SDL_Window, sdlWindowDeleter>& window() const;

   private:
    int _flags{};
    std::size_t _width{};
    std::size_t _height{};
    std::unique_ptr<SDL_Window, sdlWindowDeleter> _window = nullptr;
    std::string_view _title;
};

}  // namespace sdl

#endif  //BOMBERMAN_WINDOW_HPP
