//
// Created by Vache Gasparyan on 17.12.23.
//

#ifndef BOMBERMAN_SPRITE_FACTORY_HPP
#define BOMBERMAN_SPRITE_FACTORY_HPP

#include <string>
#include <unordered_map>

#include <sdlTextureDeleter.hpp>
#include <sprite.hpp>

namespace sdl {
class Sprite;
class SpriteFactory {
   public:
    SpriteFactory() = default;

   public:
    static void addNewSprite(const std::string& path, std::size_t id,
                             SDL_Renderer* renderer);
    static std::shared_ptr<sdl::Sprite> getSprite(std::size_t id);

   private:
    static std::unordered_map<std::size_t, std::shared_ptr<Sprite>> _sprites;
};

}  // namespace sdl

#endif  //BOMBERMAN_SPRITE_FACTORY_HPP
