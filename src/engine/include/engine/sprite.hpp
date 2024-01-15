#pragma once

#include "engine/sdlTextureDeleter.hpp"
#include "sprite_factory.hpp"
#include <engine/vec.hpp>

#include <memory>

#include "SDL3/SDL.h"

namespace sdl {

class Sprite {
   public:
    Sprite(std::unique_ptr<SDL_Texture, SdlTextureDeleter> texture, Vec4 &srcRect);
    virtual ~Sprite() = default;

   public:
    virtual void draw(SDL_Renderer* renderer, const SDL_FRect& srcRect,
              const SDL_FRect& dstRect);

   public:
    virtual std::size_t rowCount() const;
    virtual std::size_t colCount() const;
    float xRect() const;
    float yRect() const;
    float widthRect() const;
    float heightRect() const;
    SDL_FRect srcRect() const;


   protected:
    std::unique_ptr<SDL_Texture, SdlTextureDeleter> _texture{};
    SDL_FRect _srcRect{};
};

} // namespace sdl