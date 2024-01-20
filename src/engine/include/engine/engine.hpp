#pragma once

#include <engine/sprite.hpp>
#include <engine/vec.hpp>
#include <engine/renderer.hpp>
#include <engine/graphic_element.hpp>

#include <string>
#include "SDL3/SDL.h"

#include <memory>
#include <unordered_map>
#include <vector>

namespace sdl {

class Engine {
public:
    Engine(std::unique_ptr<Renderer> renderer);
    Engine(const Engine&) = delete;
    Engine& operator=(const Engine&) = delete;
    ~Engine() = default;

    void run();

    std::size_t registerGraphicElement(std::string_view assetPath,
                                       Vec4 dstRect);

    void setDrawColor(SDL_Color color);

private:
    Texture load(const std::string& assetPath);
    void present();
    void update();
    void clear();
    void draw(SDL_Renderer* renderer);

private:
    std::unique_ptr<Renderer> _renderer;
    std::unique_ptr<SpriteFactory> _factory{std::make_unique<SpriteFactory>()};
    std::unordered_map<std::size_t, std::unique_ptr<GraphicElement>>
        _graphicElements{};

private:
    static bool _initialized;
};

}  // namespace sdl