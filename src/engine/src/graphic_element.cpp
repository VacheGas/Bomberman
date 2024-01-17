//
// Created by Vache Gasparyan on 16.12.23.
//

#include "engine/graphic_element.hpp"

namespace sdl {

GraphicElement::GraphicElement(const std::shared_ptr<Sprite>& sprite, Vec4& dstRect)

    : _sprite(sprite)
    , _dstRect(dstRect),
      _animationSpeed(1) {}

void sdl::GraphicElement::draw(SDL_Renderer* renderer) {
    Vec4 currentSrcRect = _sprite->srcRect();
    currentSrcRect[0] =
        currentSrcRect[0] + currentSrcRect[2] * static_cast<float>(_currentCol);
    currentSrcRect[1] =
        currentSrcRect[1] + currentSrcRect[3] * static_cast<float>(_currentRow);
    _sprite->draw(renderer, currentSrcRect, _dstRect);
}

void sdl::GraphicElement::update() {
    auto frameNumber = _animationSpeed * static_cast<size_t>(SDL_GetTicks() / 50 - startTime);
    _currentCol = frameNumber % _sprite->colCount();
    _currentRow = frameNumber / _sprite->colCount() % _sprite->rowCount();
}

}  // namespace sdl