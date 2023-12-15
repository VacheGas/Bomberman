#pragma once

#include "sdlTextureDeleter.hpp"

#include <memory>

#include <SDL3/SDL.h>

namespace sdl {

class Sprite {
public:
    Sprite(std::unique_ptr<SDL_Texture, SdlTextureDeleter> texture, SDL_FRect srcRect, SDL_FRect dstRect);
    virtual ~Sprite() = default;

    virtual void update();
    virtual void render(SDL_Renderer* renderer);

protected:
    std::unique_ptr<SDL_Texture, SdlTextureDeleter> _texture{};
    SDL_FRect _srcRect{};
    SDL_FRect _dstRect{};
};

class AnimatableSprite : public Sprite {
public:
    AnimatableSprite(std::unique_ptr<SDL_Texture, SdlTextureDeleter> texture,
                     SDL_FRect srcRect,
                     SDL_FRect dstRect,
                     size_t rowCount,
                     size_t colCount,
                     size_t animationSpeed);

public:
    virtual void update();
    virtual void render(SDL_Renderer* renderer);

protected:
    size_t _rowCount{};
    size_t _colCount{};
    size_t _animationSpeed{};
    size_t _currentRow{};
    size_t _currentCol{};
};

} // namespace sdl