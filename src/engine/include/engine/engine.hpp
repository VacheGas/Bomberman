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

class Engine {
public:
    Engine(const std::string& title, size_t width, size_t height, int flags);
    Engine(const Engine&) = delete;
    Engine& operator=(const Engine&) = delete;
    ~Engine();

    void run();
    void registerSprite(const std::string& assetPath, Vec4 srcRect, Vec4 dstRect);

    void registerAnimatableSprite(const std::string& assetPath,
                                  Vec4 srcRect, Vec4 dstRect,
                                  size_t spriteRowCount, size_t spriteColCount,
                                  size_t animationSpeed = 1);


    std::size_t width() const;
    std::size_t height() const;
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