#pragma once

#include <graphic_element.hpp>
#include <sprite.hpp>
#include <vec.hpp>

#include <string>
#include "SDL3/SDL.h"

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

    void registerGraphicElement(const std::size_t id,
                                const std::string& assetPath, Vec4 srcRect,
                                Vec4 dstRect);

    void registerAnimatableGraphicElement(const std::size_t id,
                                          const std::string& assetPath,
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

private:
    std::string _title;
    size_t _width;
    size_t _height;
    int _flags;
    SDL_Window* _window;
    SDL_Renderer* _renderer;
    std::unordered_map<std::size_t, std::unique_ptr<GraphicElement>>
        _graphicElement{};

   private:
    static bool _initialized;
};

}  // namespace sdl