#include "engine/sprite.hpp"

namespace sdl {

Sprite::Sprite(std::unique_ptr<SDL_Texture, SdlTextureDeleter> texture, Vec4 &srcRect)
    : _texture{std::move(texture)}, _srcRect{SDL_FRect{srcRect[0], srcRect[1], srcRect[2], srcRect[3]}}  {}

// TODO : renderer should be a member of Sprite
void Sprite::draw(SDL_Renderer* renderer, const SDL_FRect& srcRect,
                  const SDL_FRect& dstRect) {
    SDL_RenderTexture(renderer, _texture.get(), &srcRect, &dstRect);
}

std::size_t Sprite::rowCount() const {
    return 1;
}
std::size_t Sprite::colCount() const {
    return 1;
}

float Sprite::xRect() const {
    return _srcRect.x;
}

float Sprite::yRect() const {
    return _srcRect.y;
}

float Sprite::widthRect() const {
    return _srcRect.w;
}

float Sprite::heightRect() const {
    return _srcRect.h;
}

SDL_FRect Sprite::srcRect() const {
    return _srcRect;
}

}  // namespace sdl