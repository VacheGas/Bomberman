#pragma once

#include <sdlTextureDeleter.hpp>
#include <sprite_factory.hpp>

#include <memory>

#include "SDL3/SDL.h"

namespace sdl {

class Sprite {
public:
    explicit Sprite(std::unique_ptr<SDL_Texture, SdlTextureDeleter> texture);
    virtual ~Sprite() = default;

   public:
    void draw(SDL_Renderer* renderer, const SDL_FRect& srcRect,
              const SDL_FRect& dstRect);

   protected:
    std::unique_ptr<SDL_Texture, SdlTextureDeleter> _texture{};
};

} // namespace sdl