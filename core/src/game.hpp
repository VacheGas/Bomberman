#pragma once

#include "game_object.hpp"
#include <SDL.h>
#include <string>

namespace sdl {

class Game {
public:
    void init(const std::string& title, size_t width, size_t height, int flags);
    static Game& getInstance();
    
    void pollEvents();
    void clear();
    void present();

    size_t width() const;
    size_t height() const;
    void setDrawColor(SDL_Color color);

private:
    void update();
    void draw(SDL_Renderer* renderer);

private:
    Game() = default;
    ~Game();
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

private:
    void initSDL(const std::string& title, size_t width, size_t height, int flags);
    void initObjects();

    void cleanSDL();
    void cleanObjects();

private:
    SDL_Window* _window;
    SDL_Renderer* _renderer;
    size_t _width;
    size_t _height;
    TextureManager _textureManager{};
    std::vector<GameObject*> _objects{};
    bool _running{};

private:
    static bool _initialized;
};

}  // namespace sdl