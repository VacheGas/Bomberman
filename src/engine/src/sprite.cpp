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
                                   size_t rowCount,
                                   size_t colCount,
                                   size_t animationSpeed)
    : Sprite{texture, srcRect, dstRect}
    , _rowCount{rowCount}
    , _colCount{colCount}
    , _animationSpeed{animationSpeed}
    , _currentRow{}
    , _currentCol{} {}

void AnimatableSprite::update() {
    // TODO: implement a mechanism to start animation from the very beginning
    auto frameNumber = _animationSpeed * int(SDL_GetTicks() / 50);
    _currentCol = frameNumber % _colCount;
    _currentRow = frameNumber / _colCount % _rowCount;
}

// TODO : remove coordinates
void AnimatableSprite::render(SDL_Renderer* renderer) {
    SDL_FRect currentSrcRect = _srcRect;
    currentSrcRect.x = _srcRect.x + _srcRect.w * static_cast<float>(_currentCol);
    currentSrcRect.y = _srcRect.y + _srcRect.h * static_cast<float>(_currentRow);
    SDL_RenderTexture(renderer, _texture, &currentSrcRect, &_dstRect);
}

} // namespace sdl