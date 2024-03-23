#pragma once

#include <engine/graphic_element.hpp>
#include <engine/input_handler.hpp>
#include <engine/renderer.hpp>
#include <engine/sprite.hpp>
#include <engine/vec.hpp>

#include <string>
#include "SDL3/SDL.h"

#include <memory>
#include <unordered_map>
#include <vector>

namespace sdl {

class Engine {
public:
    Engine(std::shared_ptr<Window> window);
    Engine(const Engine&) = delete;
    Engine& operator=(const Engine&) = delete;
    ~Engine() = default;

    void registerGraphicElement(const std::shared_ptr<GraphicElement>& element,
                                std::size_t elementID);

    void setDrawColor(SDL_Color color);

    void draw(std::size_t elementID, const Vec4& srcRect, const Vec4& dstRect);
    void present();
    void clear();
    const std::shared_ptr<Window>& window() const;

private:
    Texture load(const std::string& assetPath);
    void handleInput();

private:
    std::shared_ptr<Window> _window = nullptr;
    std::unordered_map<std::size_t, sdl::Texture> _graphicElements{};
    InputHandler _inputHandler;

private:
    static bool _initialized;
};

}  // namespace sdl