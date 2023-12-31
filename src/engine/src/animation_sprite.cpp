//
// Created by Vache Gasparyan on 30.12.23.
//

#include "engine/animation_sprite.hpp"

namespace sdl {

AnimationSprite::AnimationSprite(
    std::unique_ptr<SDL_Texture, SdlTextureDeleter> texture,
    std::size_t rowCount, std::size_t colCount)
    : Sprite(std::move(texture)), _rowCount(rowCount), _colCount(colCount) {}

size_t AnimationSprite::getRowCount() const {
    return _rowCount;
}

size_t AnimationSprite::getColCount() const {
    return _colCount;
}
}  // namespace sdl