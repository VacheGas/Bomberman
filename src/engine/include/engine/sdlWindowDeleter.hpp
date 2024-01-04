//
// Created by Vache Gasparyan on 04.01.24.
//

#ifndef BOMBERMAN_SDLWINDOWDELETER_HPP
#define BOMBERMAN_SDLWINDOWDELETER_HPP

#include <SDL3/SDL.h>

namespace sdl {

struct sdlWindowDeleter {
    void operator()(SDL_Window *window) {
        SDL_DestroyWindow(window);
    }
};

}

#endif  //BOMBERMAN_SDLWINDOWDELETER_HPP
