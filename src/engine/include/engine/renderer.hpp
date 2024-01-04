//
// Created by Vache Gasparyan on 24.12.23.
//

#ifndef BOMBERMAN_RENDERER_HPP
#define BOMBERMAN_RENDERER_HPP
#include <SDL3/SDL.h>

#include <string>

#include <engine/window.hpp>
#include <engine/sdlRendererDeleter.hpp>

namespace sdl {

class Renderer {
   public:
    Renderer() = default;
    explicit Renderer(std::unique_ptr<Window> window);

   public:
    std::unique_ptr<SDL_Renderer, sdl::sdlRendererDeleter>& renderer();


   private:
    std::unique_ptr<SDL_Renderer, sdlRendererDeleter> _renderer = nullptr;
    std::unique_ptr<Window> _window;
};

}  // namespace sdl

#endif  //BOMBERMAN_RENDERER_HPP
