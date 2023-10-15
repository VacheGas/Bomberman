#include "game_object.hpp"

namespace sdl {

GameObject::GameObject(TextureManager& textureManager, 
                       SDL_FRect initialRect,
                       const std::string& texureID)
    : _textureManager{textureManager},
      _dstRect{initialRect},
      _textureID{texureID} {}

SDL_FRect& GameObject::dstRect() {
    return _dstRect;
}

const std::string& GameObject::textureID() const {
    return _textureID;
}

void GameObject::draw(SDL_Renderer* renderer) {
    _textureManager.draw(_textureID, renderer, _dstRect);
}

void GameObject::update() {}

void GameObject::clean() {}

AnimatableGameObject::AnimatableGameObject(
        TextureManager& textureManager, 
        SDL_FRect initialRect,
        const std::string& texureID, 
        SDL_Point initialVelocity,
        SDL_Point initialAcceleration, 
        size_t spriteRowCount, 
        size_t spriteColCount,
        size_t animationSpeed)
    : GameObject {textureManager, initialRect, texureID}
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

}

void AnimatableGameObject::update() {
    _velocity.x += _acceleration.x;
    _velocity.y += _acceleration.y;

    _dstRect.x += _velocity.x;
    _dstRect.y += _velocity.y;

    auto prevFrameNumber = _currentRow * _spriteRowCount + _currentCol;
    auto nextFrameNumber = prevFrameNumber + 1;
    _currentCol = nextFrameNumber % _spriteColCount;
    _currentRow = nextFrameNumber / _spriteColCount % _spriteRowCount;
}

void AnimatableGameObject::clean() {
    GameObject::clean();
}

}  // namespace sdl
