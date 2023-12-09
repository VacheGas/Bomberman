#pragma once

#include <SDL3/SDL.h>

class InputHandler {
public:
    InputHandler();

    void update();

    bool isKeyPressed(SDL_Scancode key) const;

private:
    bool m_keyStates[SDL_NUM_SCANCODES];
};