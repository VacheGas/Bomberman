//
// Created by Vache Gasparyan on 30.12.23.
//

#pragma once

#include "sprite.hpp"

namespace sdl {

class AnimationSprite : public Sprite {
   public:
    AnimationSprite(
        std::unique_ptr<SDL_Texture, SdlTextureDeleter> texture, Vec4 &srcRect,
        size_t rowCount, size_t colCount);
    std::size_t rowCount() const override;
    std::size_t colCount() const override;

   private:
    std::size_t _rowCount{};
    std::size_t _colCount{};
};

}  // namespace sdl

