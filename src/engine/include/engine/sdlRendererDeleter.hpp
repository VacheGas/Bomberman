//
// Created by Vache Gasparyan on 24.12.23.
//

#ifndef BOMBERMAN_SDLRENDERERDELETER_HPP
#define BOMBERMAN_SDLRENDERERDELETER_HPP

#include <SDL3/SDL.h>

namespace sdl {

struct sdlRendererDeleter {
    void operator()(SDL_Renderer* renderer) {
        SDL_DestroyRenderer(renderer);
    }
};

}  // namespace sdl

#endif  //BOMBERMAN_SDLRENDERERDELETER_HPP
