//
// Created by Vache Gasparyan on 16.12.23.
//
#pragma once

#include <engine/vec.hpp>
#include "sprite.hpp"

#include <memory>
#include "SDL3/SDL.h"

namespace sdl {
class GraphicElement {
public:
    GraphicElement(const std::shared_ptr<Sprite>& sprite, Vec4& dstRect);
public:
    void draw(SDL_Renderer* renderer);
    void update();

protected:
    std::shared_ptr<Sprite> _sprite;
    Vec4 _dstRect{};

    std::size_t startTime = static_cast<size_t>(SDL_GetTicks() / 50);
    std::size_t _animationSpeed{};
    std::size_t _currentRow{};
    std::size_t _currentCol{};
};

}  // namespace sdl
