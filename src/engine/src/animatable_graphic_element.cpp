//
// Created by Vache Gasparyan on 16.12.23.
//

#include "engine/animatable_graphic_element.hpp"

// TODO: calcualtion should be moved to Sprite
void sdl::AnimatableGraphicElement::draw(SDL_Renderer* renderer) {
    SDL_FRect currentSrcRect = _sprite->srcRect();
    currentSrcRect.x =
        currentSrcRect.x + currentSrcRect.w * static_cast<float>(_currentCol);
    currentSrcRect.y =
        currentSrcRect.y + currentSrcRect.h * static_cast<float>(_currentRow);
    _sprite->draw(renderer, currentSrcRect, _dstRect);
}

void sdl::AnimatableGraphicElement::update() {
    auto frameNumber =
        _animationSpeed * static_cast<size_t>(SDL_GetTicks() / 50 - startTime);
    _currentCol = frameNumber % _sprite->colCount();
    _currentRow = frameNumber / _sprite->colCount() % _sprite->rowCount();
}

sdl::AnimatableGraphicElement::AnimatableGraphicElement(
    const std::shared_ptr<Sprite>& texture, Vec4& dstRect,
    size_t animationSpeed)
    : GraphicElement(texture, dstRect),
      _animationSpeed(animationSpeed) {}
