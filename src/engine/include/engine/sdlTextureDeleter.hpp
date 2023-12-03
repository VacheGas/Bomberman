//
// Created by Vache Gasparyan on 03.12.23.
//

#ifndef BOMBERMAN_SDLTEXTUREDELETER_HPP
#define BOMBERMAN_SDLTEXTUREDELETER_HPP

#include <SDL3/SDL.h>

namespace sdl {

    struct SdlTextureDeleter {
        void operator()(SDL_Texture *texture) const;
    };

    void SdlTextureDeleter::operator()(SDL_Texture *texture) const {
        if (texture) {
            SDL_DestroyTexture(texture);
        }
    }

}

#endif //BOMBERMAN_SDLTEXTUREDELETER_HPP
