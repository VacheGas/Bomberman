#pragma once

#include <engine/vec.hpp>
#include "engine/sdlTextureDeleter.hpp"
#include "sprite_factory.hpp"

#include "SDL3/SDL.h"

namespace sdl {

class Sprite {
public:
    Sprite(Texture texture, Vec2 frameSize);

public:
    void draw(SDL_Renderer* renderer, const Vec4& srcRect, const Vec4& dstRect);
    Vec2 frameSize() const;
    std::size_t rowCount() const;
    std::size_t colCount() const;

protected:
    Texture _texture{};
    Vec2 _frameSize{};
    std::size_t _rowCount{};
    std::size_t _colCount{};
};

}  // namespace sdl