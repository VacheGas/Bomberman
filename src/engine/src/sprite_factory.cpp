//
// Created by Vache Gasparyan on 17.12.23.
//

#include "engine/sprite_factory.hpp"
#include "engine/animation_sprite.hpp"

#include <SDL3_image/SDL_image.h>
#include <nlohmann/json.hpp>

#include <fstream>

namespace {

nlohmann::json jsonFromFile(std::string_view path) {
    std::ifstream file(path);

    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + std::string(path));
    }

    nlohmann::json data;
    file >> data;
    file.close();
    return data;
}

std::unique_ptr<SDL_Texture, sdl::SdlTextureDeleter> loadSprite(
    std::string_view path, SDL_Renderer* renderer) {
    SDL_Surface* tempSurface = IMG_Load(path.data());
    std::unique_ptr<SDL_Texture, sdl::SdlTextureDeleter> texture(
        SDL_CreateTextureFromSurface(renderer, tempSurface));
    SDL_DestroySurface(tempSurface);
    return texture;
}
}  // namespace

void sdl::SpriteFactory::addNewSprite(std::string_view assetPath, SDL_Renderer* renderer) {
    if (_sprites.contains(assetPath)) 
        return;

    auto jsonData = jsonFromFile(assetPath);
    std::string texturePath = jsonData["textureath"];
    auto x = jsonData["srcRect"]["x"];
    auto y = jsonData["srcRect"]["y"];
    auto width = jsonData["srcRect"]["width"];
    auto height = jsonData["srcRect"]["height"];
    Vec4 srcRect({x, y, width, height});

    std::unique_ptr<SDL_Texture, sdl::SdlTextureDeleter> texture = loadSprite(texturePath, renderer);
    _sprites[assetPath] = std::make_shared<Sprite>(std::move(texture), srcRect);
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
