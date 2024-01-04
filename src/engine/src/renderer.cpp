//
// Created by Vache Gasparyan on 24.12.23.
//

#include <utility>

#include "engine/renderer.hpp"
namespace sdl {

Renderer::Renderer(std::unique_ptr<Window> window) : _window(std::move(window)) {
    if (SDL_InitSubSystem(SDL_INIT_EVERYTHING) < 0) {
        throw std::runtime_error("SDL initialization error: " +
                                 std::string(SDL_GetError()));
    }
    _renderer.reset(SDL_CreateRenderer(_window->window().get(), nullptr, SDL_RENDERER_ACCELERATED));
    if (!_renderer) {
        SDL_Quit();
        throw std::runtime_error("Renderer creation error : " +
                                 std::string(SDL_GetError()));
    }
}

std::unique_ptr<SDL_Renderer, sdlRendererDeleter>& Renderer::renderer() {
    return _renderer;
}
}
