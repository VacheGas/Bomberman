#include "game_object.hpp"

namespace sdl {

GameObject::GameObject(TextureManager& textureManager, 
                       SDL_FRect initialSrcRect,
                       SDL_FRect dstRect,
                       const std::string& assetPath)
    : _textureManager{textureManager}
    , _initialSrcRect{initialSrcRect}
    , _dstRect{dstRect}
    , _assetPath{assetPath} {}

SDL_FRect& GameObject::dstRect() {
    return _dstRect;
}

const std::string& GameObject::assetPath() const {
    return _assetPath;
}

void GameObject::draw(SDL_Renderer* renderer) {
    _textureManager.draw(_assetPath, renderer, _initialSrcRect, _dstRect);
}

void GameObject::update() {}

void GameObject::clean() {}

AnimatableGameObject::AnimatableGameObject(
        TextureManager& textureManager, 
        SDL_FRect initialSrcRect,
        SDL_FRect dstRect,
        const std::string& assetPath, 
        SDL_Point initialVelocity,
        SDL_Point initialAcceleration, 
        size_t spriteRowCount, 
        size_t spriteColCount,
        size_t animationSpeed)
    : GameObject {textureManager, initialSrcRect, dstRect, assetPath}
    , _velocity{initialVelocity}
    , _acceleration{initialAcceleration}
    , _spriteRowCount{spriteRowCount}
    , _spriteColCount{spriteColCount}
    , _animationSpeed{animationSpeed} {}

SDL_Point& AnimatableGameObject::velocity() {
    return _velocity;
}

SDL_Point& AnimatableGameObject::acceleration() {
    return _acceleration;
}

void AnimatableGameObject::draw(SDL_Renderer* renderer) {
    _textureManager.draw(_assetPath, renderer, _initialSrcRect, _dstRect, _currentRow,
                         _currentCol, SDL_FLIP_NONE);
}

void AnimatableGameObject::update() {
    _velocity.x += _acceleration.x;
    _velocity.y += _acceleration.y;

    _dstRect.x += _velocity.x;
    _dstRect.y += _velocity.y;

    auto nextFrameNumber = int(SDL_GetTicks() / 100);
    _currentCol = nextFrameNumber % _spriteColCount;
    _currentRow = nextFrameNumber / _spriteColCount % _spriteRowCount;
}

void AnimatableGameObject::clean() {
    GameObject::clean();
}

}  // namespace sdl
