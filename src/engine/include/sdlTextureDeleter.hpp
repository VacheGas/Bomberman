//
// Created by Vache Gasparyan on 03.12.23.
//

#ifndef BOMBERMAN_DELETERIOUSLY_HPP
#define BOMBERMAN_DELETERIOUSLY_HPP

#include "SDL3/SDL.h"

namespace sdl {

    struct SdlTextureDeleter {
    void operator()(SDL_Texture* texture);
};

inline void SdlTextureDeleter::operator()(SDL_Texture* texture) {
    if (texture) {
        SDL_DestroyTexture(texture);
    }
}

}

#endif //BOMBERMAN_DELETERIOUSLY_HPP
