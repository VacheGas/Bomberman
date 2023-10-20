#include <engine/sprite.hpp>

namespace sdl {

Sprite::Sprite(SDL_Texture* texture, 
               SDL_FRect srcRect, 
               SDL_FRect dstRect)
    : _texture{texture}
    , _srcRect{srcRect}
    , _dstRect{dstRect} {}

void Sprite::update() {}

void Sprite::render(SDL_Renderer* renderer) {
    SDL_RenderTexture(renderer, _texture, &_srcRect, &_dstRect);
}

AnimatableSprite::AnimatableSprite(SDL_Texture* texture, 
                                   SDL_FRect srcRect,
                                   SDL_FRect dstRect, 
                                   SDL_Point velocity,
                                   SDL_Point acceleration,
                                   size_t animationSpeed, 
                                   size_t rowCount,
                                   size_t colCount)
    : Sprite{texture, srcRect, dstRect}
    , _velocity{velocity}
    , _acceleration{acceleration}
    , _animationSpeed{animationSpeed}
    , _rowCount{rowCount}
    , _colCount{colCount}
    , _currentRow{}
    , _currentCol{} {}

SDL_Point& AnimatableSprite::velocity() {
    return _velocity;
}

SDL_Point& AnimatableSprite::acceleration() {
    return _acceleration;
}

void AnimatableSprite::update() {
    _velocity.x += _acceleration.x;
    _velocity.y += _acceleration.y;
    _dstRect.x += _velocity.x;
    _dstRect.y += _velocity.y;

    auto frameNumber = int(SDL_GetTicks() / 100);
    auto _currentCol = frameNumber % _colCount;
    auto _currentRow = frameNumber / _colCount % _rowCount;
}

void AnimatableSprite::render(SDL_Renderer* renderer) {
    auto currentSrcRect = _srcRect;
    currentSrcRect.x = _srcRect.x + _srcRect.w * _currentCol;
    currentSrcRect.y = _srcRect.y + _srcRect.h + _currentRow;
    SDL_RenderTexture(renderer, _texture, &currentSrcRect, &_dstRect);
}

} // namespace sdl