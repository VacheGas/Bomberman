#include <algorithm>
#include <engine/input_handler.hpp>
#include <iostream>

sdl::InputHandler::InputHandler() {
    // Initialize the keyboard state array
    std::fill(std::begin(_keyStates), std::end(_keyStates), false);
}

// Todo should update only using scancodes
void sdl::InputHandler::update() {
    // Update the keyboard state
    SDL_PumpEvents();
    const Uint8* keyboardState = SDL_GetKeyboardState(nullptr);

    SDL_memcpy(_keyStates.data(), keyboardState, SDL_NUM_SCANCODES);
}

bool sdl::InputHandler::isKeyPressed(sdl::ENGINE_SCANCODES key) const {
    return _keyStates[castEngineScancodesToSdlScancode(supportedScancodes(),
                                                       key)];
}
