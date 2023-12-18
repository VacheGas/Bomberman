//
// Created by Vache Gasparyan on 16.12.23.
//

#include "graphic_element.hpp"

namespace sdl {
GraphicElement::GraphicElement(const std::shared_ptr<sdl::Sprite>& texture,
                               const SDL_FRect& srcRect,
                               const SDL_FRect& dstRect)
    : _texture(texture), _srcRect(srcRect), _dstRect(dstRect) {}

void GraphicElement::draw(SDL_Renderer* renderer) {
    _texture->draw(renderer, _srcRect, _dstRect);
}

void GraphicElement::update() {}

std::unordered_map<std::size_t, std::shared_ptr<Sprite>>
    SpriteFactory::_sprites;
}  // namespace sdl