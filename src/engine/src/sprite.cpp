#include "engine/sprite.hpp"

namespace sdl {

Sprite::Sprite(std::unique_ptr<SDL_Texture, SdlTextureDeleter> texture, Vec2 frameSize)
    : _texture{std::move(texture)}
    , _frameSize{frameSize}
    , _rowCount{}
    , _colCount{} {

    int width{};
    int height{};
    SDL_QueryTexture(_texture.get(), nullptr, nullptr, &width, &height);
    _rowCount = height / _frameSize[1];
    _colCount = width / _frameSize[0];
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

Vec2 Sprite::frameSize() const {
    return _frameSize;
}

}  // namespace sdl