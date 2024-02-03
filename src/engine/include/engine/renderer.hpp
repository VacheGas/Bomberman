//
// Created by Vache Gasparyan on 24.12.23.
//

#pragma once

#include <SDL3/SDL.h>

#include <string>

#include <engine/sdlRendererDeleter.hpp>
#include <engine/window.hpp>

namespace sdl {
class Window;

class Renderer {
public:
    explicit Renderer(const Window& window);

public:
    std::unique_ptr<SDL_Renderer, sdl::sdlRendererDeleter>& renderer();

private:
    std::unique_ptr<SDL_Renderer, sdlRendererDeleter> _renderer = nullptr;
};

}  // namespace sdl
