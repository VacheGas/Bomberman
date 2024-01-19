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
    auto frameSize = _sprite->frameSize();
    Vec4 srcRect({frameSize[0] * static_cast<float>(_currentCol),
                 frameSize[1] * static_cast<float>(_currentRow), 
                 frameSize[0],
                 frameSize[1]});
    _sprite->draw(renderer, srcRect, _dstRect);
}

void sdl::GraphicElement::update() {
    auto frameNumber = _animationSpeed * static_cast<size_t>(SDL_GetTicks() / 50 - startTime);
    _currentCol = frameNumber % _sprite->colCount();
    _currentRow = frameNumber / _sprite->colCount() % _sprite->rowCount();
}

}  // namespace sdl