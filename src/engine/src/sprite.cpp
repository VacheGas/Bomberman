#include "sprite.hpp"

namespace sdl {

Sprite::Sprite(std::unique_ptr<SDL_Texture, SdlTextureDeleter> texture)
    : _texture{std::move(texture)} {}

void Sprite::draw(SDL_Renderer* renderer, const SDL_FRect& srcRect,
                  const SDL_FRect& dstRect) {
    SDL_RenderTexture(renderer, _texture.get(), &srcRect, &dstRect);
}

int Sprite::width() {
    int width;
    SDL_QueryTexture(_texture.get(), nullptr, nullptr,
                     &width, nullptr);
    return width;
}

int Sprite::height() {
    int height;
    SDL_QueryTexture(_texture.get(), nullptr, nullptr,
                     nullptr, &height);
    return height;
}

} // namespace sdl