#pragma once

#include <SDL.h>
#include <string>
#include "sprite.hpp"

namespace sdl {

class Engine {
   public:
    void init(const std::string& title, size_t width, size_t height, int flags);
    void run();
    void registerObject(const std::string& assetPath, SDL_FRect initialSrcRect,
                        SDL_FRect dstRect);

    void registerAnimatableObject(const std::string& assetPath,
                                  SDL_FRect initialSrcRect, SDL_FRect dstRect,
                                  SDL_Point initialVelocity,
                                  SDL_Point initialAcceleration,
                                  size_t spriteRowCount, size_t spriteColCount,
                                  size_t animationSpeed);

    bool load(const std::string& assetPath);

    size_t width() const;
    size_t height() const;
    void setDrawColor(SDL_Color color);
    static Engine& getInstance();

   private:
    void present();
    void update();
    void clear();
    void draw(SDL_Renderer* renderer);

   private:
    Engine() = default;
    ~Engine();
    Engine(const Engine&) = delete;
    Engine& operator=(const Engine&) = delete;

   private:
    void initSDL();
    void cleanSDL();
    void cleanObjects();
    void cleanTextures();

   private:
    std::string _title;
    SDL_Window* _window;
    SDL_Renderer* _renderer;
    int _SDLFlags;
    size_t _width;
    size_t _height;
    std::unordered_map<std::string, SDL_Texture*> _textures;
    std::vector<Sprite*> _objects{};
    bool _running{};

   private:
    static bool _initialized;
};

}  // namespace sdl