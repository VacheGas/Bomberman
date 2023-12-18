//
// Created by Vache Gasparyan on 16.12.23.
//

#include "animatable_graphic_element.hpp"

void sdl::AnimatableGraphicObject::draw(SDL_Renderer* renderer) {
    auto currentSrcRect = _srcRect;
    currentSrcRect.x =
        _srcRect.x + _srcRect.w * static_cast<float>(_currentCol);
    currentSrcRect.y =
        _srcRect.y + _srcRect.h * static_cast<float>(_currentRow);
    _texture->draw(renderer, currentSrcRect, _dstRect);
}

void sdl::AnimatableGraphicObject::update() {
    auto frameNumber = _animationSpeed * static_cast<size_t>(SDL_GetTicks() / 50 - startTime);
    _currentCol = frameNumber % _colCount;
    _currentRow = frameNumber / _colCount % _rowCount;
}

sdl::AnimatableGraphicObject::AnimatableGraphicObject(
    const std::shared_ptr<Sprite>& texture, SDL_FRect& srcRect,
    SDL_FRect& dstRect, size_t rowCount, size_t colCount, size_t animationSpeed)
    : GraphicElement(texture, srcRect, dstRect),
      _rowCount(rowCount),
      _colCount(colCount),
      _animationSpeed(animationSpeed) {}
