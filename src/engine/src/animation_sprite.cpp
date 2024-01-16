//
// Created by Vache Gasparyan on 30.12.23.
//

#include "engine/animation_sprite.hpp"

namespace sdl {

AnimationSprite::AnimationSprite(
    std::unique_ptr<SDL_Texture, SdlTextureDeleter> texture, Vec4 &srcRect,
    std::size_t rowCount, std::size_t colCount)
    : Sprite(std::move(texture), srcRect), _rowCount(rowCount), _colCount(colCount) {}

size_t AnimationSprite::rowCount() const {
    return _rowCount;
}

size_t AnimationSprite::colCount() const {
    return _colCount;
}
}  // namespace sdl