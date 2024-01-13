#pragma once

#include <engine/sprite.hpp>
#include <engine/vec.hpp>

#include <SDL3/SDL.h>
#include <string>

#include <memory>
#include <unordered_map>
#include <vector>

namespace sdl {

using Texture = SDL_Texture;

/**
 * @class Engine
 * @brief Represents the core game engine for graphics rendering and management.
 */
class Engine {
public:
    /**
     * @brief Constructor for the Engine class.
     * @param title The title of the game window.
     * @param width The width of the game window.
     * @param height The height of the game window.
     * @param flags Additional flags for the game window.
     */
    Engine(const std::string& title, size_t width, size_t height, int flags);

    /**
     * @brief Copy constructor is deleted to prevent unintended copying of the engine instance.
     */
    Engine(const Engine&) = delete;

    /**
     * @brief Copy assignment operator is deleted to prevent unintended copying of the engine instance.
     */
    Engine& operator=(const Engine&) = delete;

    /**
     * @brief Destructor for the Engine class.
     */
    ~Engine();

    /**
     * @brief Initiates the game loop.
     */
    void run();

    /**
     * @brief Registers a sprite with the specified asset path and destination rectangles.
     * @param assetPath The path to the sprite's image asset.
     * @param srcRect The source rectangle defining the portion of the sprite image to render.
     * @param dstRect The destination rectangle defining where to render the sprite on the screen.
     */
    void registerSprite(const std::string& assetPath, Vec4 srcRect, Vec4 dstRect);

    /**
     * @brief Registers an animatable sprite with animation parameters.
     * @param assetPath The path to the sprite's image asset.
     * @param srcRect The source rectangle defining the portion of the sprite image to render.
     * @param dstRect The destination rectangle defining where to render the sprite on the screen.
     * @param spriteRowCount The number of rows in the sprite sheet.
     * @param spriteColCount The number of columns in the sprite sheet.
     * @param animationSpeed The speed of the animation (default is 1).
     */
    void registerAnimatableSprite(const std::string& assetPath,
                                  Vec4 srcRect, Vec4 dstRect,
                                  size_t spriteRowCount, size_t spriteColCount,
                                  size_t animationSpeed = 1);
    /**
     * @brief Retrieves the width of the game window.
     * @return The width of the game window.
     */
    std::size_t width() const;

    /**
     * @brief Retrieves the height of the game window.
     * @return The height of the game window.
     */
    std::size_t height() const;

    /**
     * @brief Sets the draw color for rendering.
     * @param color The SDL color to set.
     */
    void setDrawColor(SDL_Color color);

private:
    std::unique_ptr<Texture, SdlTextureDeleter> load(const std::string& assetPath);
    void present();
    void update();
    void clear();
    void draw(SDL_Renderer* renderer);

private:
    void initSDL();
    void cleanSDL();
    void cleanTextures();

private:
    std::string _title;
    size_t _width;
    size_t _height;
    int _flags;
    SDL_Window* _window;
    SDL_Renderer* _renderer;
    std::unordered_map<std::string, std::unique_ptr<Sprite>> _sprites{};

private:
    static bool _initialized;
};

}  // namespace sdl