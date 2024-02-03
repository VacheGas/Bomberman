//
// Created by Vache Gasparyan on 24.12.23.
//

#include "engine/renderer.hpp"

namespace sdl {

Renderer::Renderer(const Window& window) {
    _renderer.reset(SDL_CreateRenderer(window.window().get(), nullptr,
                                       SDL_RENDERER_ACCELERATED));
    if (!_renderer) {
        SDL_Quit();
        throw std::runtime_error("Renderer creation error : " +
                                 std::string(SDL_GetError()));
    }
}

std::unique_ptr<SDL_Renderer, sdlRendererDeleter>& Renderer::renderer() {
    return _renderer;
}

}  // namespace sdl
