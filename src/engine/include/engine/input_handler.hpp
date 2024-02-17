#pragma once

#include <SDL3/SDL.h>
#include <array>

class InputHandler {
public:
    InputHandler();

    void update();

    bool isKeyPressed(SDL_Scancode key) const;

private:
    std::array<bool, SDL_NUM_SCANCODES> m_keyStates;
};