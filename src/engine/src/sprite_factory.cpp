//
// Created by Vache Gasparyan on 17.12.23.
//

#include <sprite_factory.hpp>

#include <SDL3_image/SDL_image.h>

void sdl::SpriteFactory::addNewSprite(const std::string& path, std::size_t id,
                                      SDL_Renderer* renderer) {
    SDL_Surface* tempSurface = IMG_Load(path.c_str());
    std::unique_ptr<SDL_Texture, SdlTextureDeleter> texture(
        SDL_CreateTextureFromSurface(renderer, tempSurface));
    SDL_DestroySurface(tempSurface);
    if (_sprites[id] == nullptr) {
        _sprites[id] = std::make_shared<Sprite>(std::move(texture));
    }
}

std::shared_ptr<sdl::Sprite> sdl::SpriteFactory::getSprite(std::size_t id) {
    return _sprites[id];
}
