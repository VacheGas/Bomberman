//
// Created by Vache Gasparyan on 30.12.23.
//

#ifndef BOMBERMAN_ANIMATION_SPRITE_HPP
#define BOMBERMAN_ANIMATION_SPRITE_HPP

#include "sprite.hpp"

namespace sdl {

class AnimationSprite : public Sprite {
   public:
    AnimationSprite(
        std::unique_ptr<SDL_Texture, SdlTextureDeleter> texture,
        size_t rowCount, size_t colCount);
    std::size_t getRowCount() const override;
    std::size_t getColCount() const override;

   public:


   private:
    std::size_t _rowCount{};
    std::size_t _colCount{};
};

}  // namespace sdl

#endif  //BOMBERMAN_ANIMATION_SPRITE_HPP
