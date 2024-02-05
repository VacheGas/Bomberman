//
// Created by Vache Gasparyan on 24.12.23.
//

#pragma once

#include <SDL3/SDL.h>

#include <string>

#include <engine/window.hpp>

namespace sdl {
class Window;

class Renderer {
public:
    explicit Renderer(const Window& window);

public:
    std::shared_ptr<SDL_Renderer>& renderer();

private:
    std::shared_ptr<SDL_Renderer> _renderer = nullptr;
};

}  // namespace sdl
