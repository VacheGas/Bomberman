//
// Created by Vache Gasparyan on 16.12.23.
//

#ifndef BOMBERMAN_ANIMATABLE_GRAPHIC_ELEMENT_HPP
#define BOMBERMAN_ANIMATABLE_GRAPHIC_ELEMENT_HPP

#include <graphic_element.hpp>

namespace sdl {

class AnimatableGraphicElement : public GraphicElement {
   public:
    AnimatableGraphicElement() = default;
    AnimatableGraphicElement(const std::shared_ptr<Sprite>& texture,
                            SDL_FRect& srcRect, SDL_FRect& dstRect,
                            size_t rowCount, size_t colCount,
                            size_t animationSpeed);

    void update() override;
    void draw(SDL_Renderer* renderer) override;

   protected:
    std::size_t startTime =  static_cast<size_t>(SDL_GetTicks() / 50);
    std::size_t _rowCount{};
    std::size_t _colCount{};
    std::size_t _animationSpeed{};
    std::size_t _currentRow = 1;
    std::size_t _currentCol = 1;
};

}  // namespace sdl

#endif  //BOMBERMAN_ANIMATABLE_GRAPHIC_ELEMENT_HPP
