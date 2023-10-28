#pragma once

#include <engine/sprite.hpp>
#include <engine/vec.hpp>

#include <SDL.h>
#include <string>

namespace sdl {

class Engine {
public:
    Engine(const std::string& title, size_t width, size_t height, int flags);
    Engine(const Engine&) = delete;
    Engine& operator=(const Engine&) = delete;
    ~Engine();

    void run();
    void registerSprite(const std::string& assetPath, SDL_FRect initialSrcRect,
                        SDL_FRect dstRect);

    void registerAnimatableSprite(const std::string& assetPath,
                                  SDL_FRect initialSrcRect, SDL_FRect dstRect,
                                  size_t spriteRowCount, size_t spriteColCount,
                                  size_t animationSpeed);

    bool load(const std::string& assetPath);

    size_t width() const;
    size_t height() const;
    void setDrawColor(SDL_Color color);

private:
    void present();
    void update();
    void clear();
    void draw(SDL_Renderer* renderer);

private:
    void initSDL();
    void cleanSDL();
    void cleanSprites();
    void cleanTextures();

private:
    std::string _title;
    size_t _width;
    size_t _height;
    int _flags;
    SDL_Window* _window;
    SDL_Renderer* _renderer;
    std::unordered_map<std::string, SDL_Texture*> _textures;
    std::vector<Sprite*> _sprites{};
    bool _running{};

private:
    static bool _initialized;
};

}  // namespace sdl