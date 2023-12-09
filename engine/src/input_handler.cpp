#include <engine/input_handler.hpp>

InputHandler::InputHandler() {
    // Initialize the keyboard state array
    for (int i = 0; i < SDL_NUM_SCANCODES; i++) {
        m_keyStates[i] = false;
    }
}

void InputHandler::update() {
    // Update the keyboard state
    SDL_PumpEvents();
    const Uint8* keyboardState = SDL_GetKeyboardState(NULL);
    SDL_memcpy(m_keyStates, keyboardState, SDL_NUM_SCANCODES);
}

bool InputHandler::isKeyPressed(SDL_Scancode key) const {
    if (key >= 0 && key < SDL_NUM_SCANCODES) {
        return m_keyStates[key];
    }
    return false;
}