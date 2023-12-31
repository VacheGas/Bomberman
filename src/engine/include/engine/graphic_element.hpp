//
// Created by Vache Gasparyan on 16.12.23.
//

#ifndef BOMBERMAN_GRAPHIC_ELEMENT_HPP
#define BOMBERMAN_GRAPHIC_ELEMENT_HPP

#include "sprite.hpp"

#include <memory>
#include "SDL3/SDL.h"

namespace sdl {
class GraphicElement {
   public:
    GraphicElement() = default;

    GraphicElement(const std::shared_ptr<sdl::Sprite>& sharedPtr,
                   const SDL_FRect& rect, const SDL_FRect& rect1);

    virtual ~GraphicElement() = default;

   public:
    virtual void draw(SDL_Renderer* renderer);
    virtual void update();

   protected:
    std::shared_ptr<Sprite> _texture;
    SDL_FRect _srcRect{};
    SDL_FRect _dstRect{};
};

}  // namespace sdl

#endif  //BOMBERMAN_GRAPHIC_ELEMENT_HPP
