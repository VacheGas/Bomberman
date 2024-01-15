//
// Created by Vache Gasparyan on 17.12.23.
//

#pragma once

#include <string>
#include <unordered_map>
#include <unordered_set>

#include "engine/sdlTextureDeleter.hpp"
#include "engine/sprite.hpp"
#include <engine/vec.hpp>

namespace sdl {
class Engine;
class Sprite;

class SpriteFactory {
   public:
    SpriteFactory() = default;

   private:
    void addNewSprite(std::string_view path,
                             SDL_Renderer* renderer, Vec4 &srcRect);
    void addNewAnimationSprite(std::string_view path,
                      SDL_Renderer* renderer, Vec4 &srcRect, std::size_t rowCount, std::size_t colCount);
    std::shared_ptr<sdl::Sprite> getSprite(std::string_view id);
   private:
    std::unordered_map<std::string_view, std::shared_ptr<Sprite>> _sprites;
    friend class Engine;
};

}  // namespace sdl
