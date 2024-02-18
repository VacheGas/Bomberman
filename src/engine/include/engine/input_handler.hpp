#pragma once

#include <engine/actions.hpp>

#include <SDL3/SDL.h>

#include <array>
namespace sdl {
using PermittedScancodes =
    std::array<std::pair<sdl::ENGINE_SCANCODES, SDL_Scancode>,
               static_cast<std::size_t>(sdl::ENGINE_SCANCODES::COUNT)>;

class InputHandler {
public:
    InputHandler();

    void update();

    [[nodiscard]] bool isKeyPressed(sdl::ENGINE_SCANCODES key) const;

protected:
    static constexpr std::size_t castEngineScancodesToSdlScancode(
        const PermittedScancodes& allowedScancodes,
        sdl::ENGINE_SCANCODES scancode);
    static constexpr sdl::ENGINE_SCANCODES castSdlScancodeToEngineScancode(
        const PermittedScancodes& allowedScancodes, SDL_Scancode scancode);
    static constexpr PermittedScancodes supportedScancodes();

private:
    std::array<bool, SDL_NUM_SCANCODES> _keyStates;
};
}  // namespace sdl

constexpr std::size_t sdl::InputHandler::castEngineScancodesToSdlScancode(
    const sdl::PermittedScancodes& allowedScancodes,
    sdl::ENGINE_SCANCODES scancode) {
    return std::find_if(
               std::cbegin(allowedScancodes), std::cend(allowedScancodes),
               [&scancode](const auto& it) { return it.first == scancode; })
        ->second;
}

constexpr sdl::ENGINE_SCANCODES
sdl::InputHandler::castSdlScancodeToEngineScancode(
    const PermittedScancodes& allowedScancodes, SDL_Scancode scancode) {
    return std::find_if(
               std::cbegin(allowedScancodes), std::cend(allowedScancodes),
               [&scancode](const auto& it) { return it.second == scancode; })
        ->first;
}

constexpr sdl::PermittedScancodes sdl::InputHandler::supportedScancodes() {
    constexpr sdl::PermittedScancodes allowedScancodes{
        std::pair{sdl::ENGINE_SCANCODES::W, SDL_SCANCODE_W},
        {sdl::ENGINE_SCANCODES::S, SDL_SCANCODE_S},
        {sdl::ENGINE_SCANCODES::A, SDL_SCANCODE_A},
        {sdl::ENGINE_SCANCODES::D, SDL_SCANCODE_D},
        {sdl::ENGINE_SCANCODES::SPACE, SDL_SCANCODE_SPACE}};
    static_assert(std::find_if(std::cbegin(allowedScancodes),
                               std::cend(allowedScancodes), [](const auto& it) {
                                   return it.second == SDL_SCANCODE_UNKNOWN;
                               }) == std::cend(allowedScancodes));
    return allowedScancodes;
}
