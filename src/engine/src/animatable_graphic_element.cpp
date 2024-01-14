//
// Created by Vache Gasparyan on 16.12.23.
//

#include "engine/animatable_graphic_element.hpp"

void sdl::AnimatableGraphicElement::draw(SDL_Renderer* renderer) {
    auto currentSrcRect = _srcRect;
    currentSrcRect.x =
        _srcRect.x + _srcRect.w * static_cast<float>(_currentCol);
    currentSrcRect.y =
        _srcRect.y + _srcRect.h * static_cast<float>(_currentRow);
    _sprite->draw(renderer, currentSrcRect, _dstRect);
}

void sdl::AnimatableGraphicElement::update() {
    auto frameNumber =
        _animationSpeed * static_cast<size_t>(SDL_GetTicks() / 50 - startTime);
    _currentCol = frameNumber % _sprite->getColCount();
    _currentRow = frameNumber / _sprite->getColCount() % _sprite->getRowCount();
}

sdl::AnimatableGraphicElement::AnimatableGraphicElement(
    const std::shared_ptr<Sprite>& texture, Vec4& srcRect, Vec4& dstRect,
    size_t animationSpeed)
    : GraphicElement(texture, srcRect, dstRect),
      _animationSpeed(animationSpeed) {}
