//
// Created by Vache Gasparyan on 16.12.23.
//

#pragma once

#include "graphic_element.hpp"
#include <engine/vec.hpp>
namespace sdl {

class AnimatableGraphicElement : public GraphicElement {
   public:
    AnimatableGraphicElement() = default;
    AnimatableGraphicElement(const std::shared_ptr<Sprite>& sprite, Vec4& dstRect,
                            size_t animationSpeed);

    void update() override;
    void draw(SDL_Renderer* renderer) override;

   protected:
    std::size_t startTime =  static_cast<size_t>(SDL_GetTicks() / 50);
    std::size_t _animationSpeed{};
    std::size_t _currentRow = 1;
    std::size_t _currentCol = 1;
};

}  // namespace sdl
