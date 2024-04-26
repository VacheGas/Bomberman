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

class DrawingContext {
public:
    DrawingContext(std::shared_ptr<Window> window);
    DrawingContext(const DrawingContext&) = delete;
    DrawingContext& operator=(const DrawingContext&) = delete;
    ~DrawingContext() = default;

    void registerSprite(const std::shared_ptr<sdl::Sprite>& element,
                        std::size_t elementID);

    void setDrawColor(SDL_Color color);

    void draw(std::size_t elementID, const Vec4& srcRect, const Vec4& dstRect);
    void present();
    void clear();
    [[nodiscard]] const std::shared_ptr<Window>& window() const;

private:
    void handleInput();

private:
    std::shared_ptr<Window> _window = nullptr;
    std::unordered_map<std::size_t,
                       std::unique_ptr<SDL_Texture, sdl::SdlTextureDeleter>>
        _graphicElements{};
    InputHandler _inputHandler;

private:
    static bool _initialized;
};

}  // namespace sdl