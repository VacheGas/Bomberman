#pragma once

#include "game_object.hpp"
#include <SDL.h>
#include <string>

namespace sdl {

class Game {
public:
    void init(const std::string& title, size_t width, size_t height, int flags);
    void pollEvents();
    void registerObject(const std::string& assetPath,
                        SDL_FRect initialSrcRect,
                        SDL_FRect dstRect);

    void registerAnimatableObject(const std::string& assetPath,
                                  SDL_FRect initialSrcRect,
                                  SDL_FRect dstRect,
                                  SDL_Point initialVelocity,
                                  SDL_Point initialAcceleration,
                                  size_t spriteRowCount, size_t spriteColCount,
                                  size_t animationSpeed);

    size_t width() const;
    size_t height() const;
    void setDrawColor(SDL_Color color);
    static Game& getInstance();

private:
    void present();
    void update();
    void clear();
    void draw(SDL_Renderer* renderer);

private:
    Game() = default;
    ~Game();
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

private:
    void initSDL();
    void cleanSDL();
    void cleanObjects();

private:
    std::string _title;
    SDL_Window* _window;
    SDL_Renderer* _renderer;
    int _SDLFlags;
    size_t _width;
    size_t _height;
    TextureManager _textureManager{};
    std::vector<GameObject*> _objects{};
    bool _running{};

private:
    static bool _initialized;
};

}  // namespace sdl