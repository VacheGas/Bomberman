#include "engine/sprite.hpp"

namespace sdl {

Sprite::Sprite(std::unique_ptr<SDL_Surface, sdl::SdlSurfaceDeleter> imageData,
               Vec2 frameSize)
    : _imageData{std::move(imageData)},
      _frameSize{frameSize},
      _rowCount{},
      _colCount{} {

    _rowCount = _imageData->h / static_cast<int>(_frameSize[1]);
    _colCount = _imageData->w / static_cast<int>(_frameSize[0]);
}

std::size_t Sprite::rowCount() const {
    return _rowCount;
}
std::size_t Sprite::colCount() const {
    return _colCount;
}

Vec2 Sprite::frameSize() const {
    return _frameSize;
}

SDL_Surface* sdl::Sprite::data() {
    return _imageData.get();
}

std::size_t sdl::Sprite::height() {
    return _imageData->h;
}

std::size_t sdl::Sprite::width() {
    return _imageData->w;
}

}  // namespace sdl