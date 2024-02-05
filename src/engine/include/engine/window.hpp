//
// Created by Vache Gasparyan on 04.01.24.
//

#pragma once

#include <SDL3/SDL.h>

#include <engine/renderer.hpp>
#include "sdlWindowDeleter.hpp"

#include <memory>
#include <string_view>

namespace sdl {
class Renderer;
class Window {
public:
    Window(std::string_view title, size_t width, size_t height, int flag);
    Window(Window&& window) = default;
    ~Window();

public:
    [[nodiscard]] const std::shared_ptr<Renderer>& renderer() const;
    [[nodiscard]] const std::unique_ptr<SDL_Window, sdlWindowDeleter>& window()
        const;
    [[nodiscard]] int flags() const noexcept;
    [[nodiscard]] std::size_t width() const noexcept;
    [[nodiscard]] std::size_t height() const noexcept;
    [[nodiscard]] const std::string_view& title() const;

private:
    int _flags{};
    std::size_t _width{};
    std::size_t _height{};
    std::unique_ptr<SDL_Window, sdlWindowDeleter> _window = nullptr;
    std::shared_ptr<Renderer> _renderer;
    std::string_view _title;
};

}  // namespace sdl
