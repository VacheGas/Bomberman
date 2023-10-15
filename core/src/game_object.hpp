#pragma once

#include "texture_manager.hpp"
#include <SDL.h>

namespace sdl {

class GameObject {
public:
    GameObject(TextureManager& textureManager,
               SDL_FRect initialRect, 
               const std::string& texureID);
    virtual ~GameObject() = default;
    SDL_FRect& dstRect();
    const std::string& textureID() const;

public:
    virtual void draw(SDL_Renderer* renderer);
    virtual void update();
    virtual void clean();

protected:
    TextureManager& _textureManager;
    SDL_FRect _dstRect{};
    std::string _textureID{};
};

class AnimatableGameObject : public GameObject {
public:
    AnimatableGameObject(TextureManager& textureManager,
                         SDL_FRect initialRect, 
                         const std::string& texureID,
                         SDL_Point initialVelocity, 
                         SDL_Point initialAcceleration,
                         size_t spriteRowCount, 
                         size_t spriteColCount,
                         size_t animationSpeed);

    SDL_Point& velocity();
    SDL_Point& acceleration();

public:
    virtual void draw(SDL_Renderer* renderer) override;
    virtual void update() override;
    virtual void clean() override;

protected:
    SDL_Point _velocity{};
    SDL_Point _acceleration{};
    size_t _spriteRowCount{};
    size_t _spriteColCount{};
    size_t _animationSpeed{};
    size_t _currentRow{};
    size_t _currentCol{};
};

}  // namespace sdl