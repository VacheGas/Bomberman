//
// Created by Vache Gasparyan on 24.12.23.
//

#include "engine/renderer.hpp"

namespace sdl {

Renderer::Renderer(const Window& window) {
    auto sdlRendererDeletern = [](SDL_Renderer* renderer) {
        SDL_DestroyRenderer(renderer);
    };
    _renderer = std::shared_ptr<SDL_Renderer>(
        (SDL_CreateRenderer(window.window().get(), nullptr,
                            SDL_RENDERER_ACCELERATED)),
        sdlRendererDeletern);
    if (!_renderer) {
        SDL_Quit();
        throw std::runtime_error("Renderer creation error : " +
                                 std::string(SDL_GetError()));
    }
}

std::shared_ptr<SDL_Renderer>& Renderer::renderer() {
    return _renderer;
}

}  // namespace sdl
