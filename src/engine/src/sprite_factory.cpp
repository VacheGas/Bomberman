//
// Created by Vache Gasparyan on 17.12.23.
//

#include "engine/sprite_factory.hpp"
#include "engine/animation_sprite.hpp"

#include <SDL3_image/SDL_image.h>
namespace {
std::unique_ptr<SDL_Texture, sdl::SdlTextureDeleter> loadSprite(
    std::string_view path, SDL_Renderer* renderer) {
    SDL_Surface* tempSurface = IMG_Load(path.data());
    std::unique_ptr<SDL_Texture, sdl::SdlTextureDeleter> texture(
        SDL_CreateTextureFromSurface(renderer, tempSurface));
    SDL_DestroySurface(tempSurface);
    return texture;
}
}  // namespace

void sdl::SpriteFactory::addNewSprite(std::string_view path,
                                      SDL_Renderer* renderer, Vec4 &srcRect) {
    if (_sprites.contains(path))
        return;
    std::unique_ptr<SDL_Texture, sdl::SdlTextureDeleter> texture =
        loadSprite(path, renderer);
    _sprites[path] = std::make_shared<Sprite>(std::move(texture), srcRect);
}

std::shared_ptr<sdl::Sprite> sdl::SpriteFactory::getSprite(
    std::string_view id) {
    return _sprites[id];
}
void sdl::SpriteFactory::addNewAnimationSprite(std::string_view path,
                                               SDL_Renderer* renderer, Vec4 &srcRect,
                                               std::size_t rowCount,
                                               std::size_t colCount) {
    if (_sprites.contains(path))
        return;
    std::unique_ptr<SDL_Texture, sdl::SdlTextureDeleter> texture =
        loadSprite(path, renderer);
    _sprites[path] = std::make_shared<sdl::AnimationSprite>(std::move(texture), srcRect,
                                                            rowCount, colCount);
}
