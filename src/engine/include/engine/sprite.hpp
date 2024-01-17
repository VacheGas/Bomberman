#pragma once

#include <engine/vec.hpp>
#include "engine/sdlTextureDeleter.hpp"
#include "sprite_factory.hpp"

#include <memory>

#include "SDL3/SDL.h"

namespace sdl {

class Sprite {
public:
    Sprite(std::unique_ptr<SDL_Texture, SdlTextureDeleter> texture,
           Vec4& srcRect, size_t rowCount, size_t colCount);
public:
    void draw(SDL_Renderer* renderer, const Vec4& srcRect, const Vec4& dstRect);
public:
    Vec4 srcRect() const;
    std::size_t rowCount() const;
    std::size_t colCount() const;

protected:
    std::unique_ptr<SDL_Texture, SdlTextureDeleter> _texture{};
    Vec4 _srcRect{};
    std::size_t _rowCount{};
    std::size_t _colCount{};
};

}  // namespace sdl