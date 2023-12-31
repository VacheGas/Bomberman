//
// Created by Vache Gasparyan on 16.12.23.
//

#include "engine/graphic_element.hpp"

namespace sdl {
GraphicElement::GraphicElement(const std::shared_ptr<sdl::Sprite>& sprite,
                               const SDL_FRect& srcRect,
                               const SDL_FRect& dstRect)
    : _sprite(sprite), _srcRect(srcRect), _dstRect(dstRect) {}

void GraphicElement::draw(SDL_Renderer* renderer) {
    _sprite->draw(renderer, _srcRect, _dstRect);
}

void GraphicElement::update() {}

}  // namespace sdl