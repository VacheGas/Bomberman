//
// Created by Vache Gasparyan on 17.12.23.
//

#include "engine/sprite_factory.hpp"
#include "engine/sprite.hpp"

#include <SDL3_image/SDL_image.h>
#include <nlohmann/json.hpp>

#include <fstream>
namespace {

nlohmann::json jsonFromFile(std::string_view assetPath) {
    std::ifstream file(assetPath);

    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + std::string(assetPath));
    }

    nlohmann::json data;
    file >> data;
    file.close();
    return data;
}

std::unique_ptr<SDL_Texture, sdl::SdlTextureDeleter> loadSprite(
    std::string_view assetPath, SDL_Renderer* renderer) {
    SDL_Surface* tempSurface = IMG_Load(assetPath.data());
    std::unique_ptr<SDL_Texture, sdl::SdlTextureDeleter> texture(
        SDL_CreateTextureFromSurface(renderer, tempSurface));
    SDL_DestroySurface(tempSurface);
    return texture;
}

}  // namespace

std::shared_ptr<sdl::Sprite> sdl::SpriteFactory::getSprite(
    std::string_view id) {
    return _sprites[id];
}
void sdl::SpriteFactory::addNewSprite(std::string_view assetPath,
                                    SDL_Renderer* renderer,
                                    std::size_t rowCount,
                                    std::size_t colCount) {
    if (_sprites.contains(assetPath))
        return;

    auto jsonData = jsonFromFile(assetPath);
    std::string texturePath = jsonData["texturePath"];
    auto x = jsonData["srcRect"]["x"];
    auto y = jsonData["srcRect"]["y"];
    auto width = jsonData["srcRect"]["width"];
    auto height = jsonData["srcRect"]["height"];
    Vec4 srcRect({x, y, width, height});

    auto texture = loadSprite(texturePath, renderer);
    _sprites[assetPath] = std::make_shared<sdl::Sprite>(std::move(texture), srcRect,
                                                            rowCount, colCount);
}
