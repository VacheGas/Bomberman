#include "engine/sprite.hpp"

namespace sdl {

Sprite::Sprite(std::unique_ptr<SDL_Texture, SdlTextureDeleter> texture, Vec4& srcRect)
    : _texture{std::move(texture)}
    , _srcRect{srcRect}
    , _rowCount{}
    , _colCount{} {

    int width{};
    int height{};
    SDL_QueryTexture(_texture.get(), nullptr, nullptr, &width, &height);
    _rowCount = height / _srcRect[3];
    _colCount = width / _srcRect[2];
}

// TODO : renderer should be a member of Sprite
void Sprite::draw(SDL_Renderer* renderer, const Vec4& srcRect, const Vec4& dstRect) {
    SDL_FRect src;
    src.x = srcRect[0];
    src.y = srcRect[1];
    src.w = srcRect[2];
    src.h = srcRect[3];

    SDL_FRect dst;
    dst.x = dstRect[0];
    dst.y = dstRect[1];
    dst.w = dstRect[2];
    dst.h = dstRect[3];

    SDL_RenderTexture(renderer, _texture.get(), &src, &dst);
}

std::size_t Sprite::rowCount() const {
    return _rowCount;
}
std::size_t Sprite::colCount() const {
    return _colCount;
}

Vec4 Sprite::srcRect() const {
    return _srcRect;
}

}  // namespace sdl