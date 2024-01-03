//
// Created by Vache Gasparyan on 16.12.23.
//
#pragma once

#include "sprite.hpp"
#include <engine/vec.hpp>

#include <memory>
#include "SDL3/SDL.h"

namespace sdl {
class GraphicElement {
   public:
    GraphicElement() = default;

    GraphicElement(const std::shared_ptr<sdl::Sprite>& sharedPtr,
                   const Vec4& rect, const Vec4& rect1);

    virtual ~GraphicElement() = default;

   public:
    virtual void draw(SDL_Renderer* renderer);
    virtual void update();

   protected:
    std::shared_ptr<Sprite> _sprite;
    SDL_FRect _srcRect{};
    SDL_FRect _dstRect{};
};

}  // namespace sdl

