#pragma once

#include <engine/vec.hpp>
#include "engine/sdlSurfaceDeleter.hpp"
#include "sprite_factory.hpp"

#include "SDL3/SDL.h"

namespace sdl {

class Sprite {
public:
    Sprite(std::unique_ptr<SDL_Surface, sdl::SdlSurfaceDeleter> imageData,
           Vec2 frameSize);

public:
    Vec2 frameSize() const;
    std::size_t rowCount() const;
    std::size_t colCount() const;
    SDL_Surface* data();
    std::size_t height();
    std::size_t width();

protected:
    std::unique_ptr<SDL_Surface, sdl::SdlSurfaceDeleter> _imageData;
    Vec2 _frameSize{};
    std::size_t _rowCount{};
    std::size_t _colCount{};
};

}  // namespace sdl