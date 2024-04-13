//
// Created by Vache Gasparyan on 16.12.23.
//

#include "engine/graphic_element.hpp"

namespace sdl {

GraphicElement::GraphicElement(const std::shared_ptr<Sprite>& sprite,
                               const Vec4& dstRect)

    : _sprite(sprite), _dstRect(dstRect), _animationSpeed(1) {}

void sdl::GraphicElement::update() {
    size_t frameNumber =
        _animationSpeed * static_cast<size_t>(SDL_GetTicks() / 50 - startTime);
    _currentCol = frameNumber % _sprite->colCount();
    _currentRow = frameNumber / _sprite->colCount() % _sprite->rowCount();
}
// Todo will adding new member srcRect
Vec4 sdl::GraphicElement::srcRect() {
    return Vec4({_sprite->frameSize()[0] * static_cast<float>(_currentCol),
                 _sprite->frameSize()[1] * static_cast<float>(_currentRow),
                 _sprite->frameSize()[0], _sprite->frameSize()[1]});
}

Vec2 sdl::GraphicElement::frameSize() {
    return _sprite->frameSize();
}

const Vec4& sdl::GraphicElement::dstRect() {
    return _dstRect;
}

SDL_Surface* GraphicElement::data() {
    return _sprite->data();
}

std::shared_ptr<Sprite>& sdl::GraphicElement::sprite() {
    return _sprite;
}

}  // namespace sdl