//
// Created by Vache Gasparyan on 17.03.24.
//

#ifndef BOMBERMAN_SDLSURFACEDELETER_HPP
#define BOMBERMAN_SDLSURFACEDELETER_HPP

#include "SDL3/SDL.h"

namespace sdl {

struct SdlSurfaceDeleter {
    void operator()(SDL_Surface* texture);
};

inline void SdlSurfaceDeleter::operator()(SDL_Surface* texture) {
    if (texture) {
        SDL_DestroySurface(texture);
    }
}

}  // namespace sdl

#endif  //BOMBERMAN_SDLSURFACEDELETER_HPP
