#pragma once

#include "sdlTextureDeleter.hpp"

#include <memory>

#include <SDL3/SDL.h>

namespace sdl {

/**
 * @class Sprite
 * @brief Represents a basic sprite with texture and rendering information.
 */
class Sprite {
public:
    /**
     * @brief Constructor for the Sprite class.
     * @param texture A unique pointer to the SDL_Texture associated with the sprite.
     * @param srcRect The source rectangle defining the portion of the sprite image to render.
     * @param dstRect The destination rectangle defining where to render the sprite on the screen.
     */
    Sprite(std::unique_ptr<SDL_Texture, SdlTextureDeleter> texture, SDL_FRect srcRect, SDL_FRect dstRect);

    /**
     * @brief Virtual destructor for the Sprite class.
     */
    virtual ~Sprite() = default;

    /**
     * @brief Virtual function to update the sprite's state.
     */
    virtual void update();

    /**
     * @brief Virtual function to render the sprite using the provided renderer.
     * @param renderer The SDL_Renderer used for rendering the sprite.
     */
    virtual void render(SDL_Renderer* renderer);

protected:
    std::unique_ptr<SDL_Texture, SdlTextureDeleter> _texture{}; /**< A unique pointer to the SDL_Texture associated with the sprite. */
    SDL_FRect _srcRect{}; /**< The source rectangle defining the portion of the sprite image to render. */
    SDL_FRect _dstRect{}; /**< The destination rectangle defining where to render the sprite on the screen. */
};

/**
 * @class AnimatableSprite
 * @brief Represents an animatable sprite with additional animation parameters.
 */
class AnimatableSprite : public Sprite {
public:
    /**
     * @brief Constructor for the AnimatableSprite class.
     * @param texture A unique pointer to the SDL_Texture associated with the sprite.
     * @param srcRect The source rectangle defining the portion of the sprite image to render.
     * @param dstRect The destination rectangle defining where to render the sprite on the screen.
     * @param rowCount The number of rows in the sprite sheet.
     * @param colCount The number of columns in the sprite sheet.
     * @param animationSpeed The speed of the animation.
     */
    AnimatableSprite(std::unique_ptr<SDL_Texture, SdlTextureDeleter> texture,
                     SDL_FRect srcRect,
                     SDL_FRect dstRect,
                     size_t rowCount,
                     size_t colCount,
                     size_t animationSpeed);

public:
    /**
     * @brief Virtual function to update the animatable sprite's state.
     */
    virtual void update();

    /**
     * @brief Virtual function to render the animatable sprite using the provided renderer.
     * @param renderer The SDL_Renderer used for rendering the sprite.
     */
    virtual void render(SDL_Renderer* renderer);

protected:
    size_t _rowCount{}; /**< The number of rows in the sprite sheet. */
    size_t _colCount{}; /**< The number of columns in the sprite sheet. */
    size_t _animationSpeed{}; /**< The speed of the animation. */
    size_t _currentRow{}; /**< The current row in the sprite sheet for animation. */
    size_t _currentCol{}; /**< The current column in the sprite sheet for animation. */
};

} // namespace sdl