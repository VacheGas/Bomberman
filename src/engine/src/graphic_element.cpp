//
// Created by Vache Gasparyan on 16.12.23.
//

#include "engine/graphic_element.hpp"

namespace sdl {
GraphicElement::GraphicElement(const std::shared_ptr<sdl::Sprite>& sprite,
                               const Vec4& dstRect)
    : _sprite(sprite),
      _dstRect(SDL_FRect{dstRect[0], dstRect[1], dstRect[2], dstRect[3]}) {}

void GraphicElement::draw(SDL_Renderer* renderer) {
    _sprite->draw(renderer, _sprite->srcRect(), _dstRect);
}

void GraphicElement::update() {}

}  // namespace sdl