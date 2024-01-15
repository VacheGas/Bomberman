#pragma once

#include "graphic_element.hpp"
#include "sprite.hpp"
#include "vec.hpp"

#include <string>
#include "SDL3/SDL.h"

#include <memory>
#include <unordered_map>
#include <vector>

namespace sdl {

using Texture = SDL_Texture;

class Engine {
public:
    Engine(std::string_view, size_t width, size_t height, int flags);
    Engine(const Engine&) = delete;
    Engine& operator=(const Engine&) = delete;
    ~Engine();

    void run();

    std::size_t registerGraphicElement(std::string_view assetPath,
                                       Vec4 srcRect);

    std::size_t registerAnimatableGraphicElement(std::string_view assetPath,
                                                 Vec4 srcRect,
                                                 size_t spriteRowCount,
                                                 size_t spriteColCount);

    std::size_t width() const;
    std::size_t height() const;
    void setDrawColor(SDL_Color color);

private:
    std::unique_ptr<Texture, SdlTextureDeleter> load(
        const std::string& assetPath);
    void present();
    void update();
    void clear();
    void draw(SDL_Renderer* renderer);

private:
    void initSDL();
    void cleanSDL();

private:
    std::string_view _title;
    size_t _width;
    size_t _height;
    int _flags;
    SDL_Window* _window;
    SDL_Renderer* _renderer;
    std::unordered_map<std::size_t, std::unique_ptr<GraphicElement>>
        _graphicElements{};
    std::unique_ptr<SpriteFactory> _factory{std::make_unique<SpriteFactory>()};

private:
    static bool _initialized;
};

}  // namespace sdl