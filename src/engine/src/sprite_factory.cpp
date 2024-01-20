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
        throw std::runtime_error("Failed to open file: " +
                                 std::string(assetPath));
    }

    nlohmann::json data;
    file >> data;
    file.close();
    return data;
}

sdl::Texture loadSprite(std::string_view assetPath, SDL_Renderer* renderer) {
    SDL_Surface* tempSurface = IMG_Load(assetPath.data());
    sdl::Texture texture(SDL_CreateTextureFromSurface(renderer, tempSurface));
    SDL_DestroySurface(tempSurface);
    return texture;
}

}  // namespace

std::shared_ptr<sdl::Sprite> sdl::SpriteFactory::getSprite(
    std::string_view id) {
    return _sprites[id];
}
void sdl::SpriteFactory::addNewSprite(std::string_view assetPath,
                                      SDL_Renderer* renderer) {
    if (_sprites.contains(assetPath))
        return;

    nlohmann::json jsonData = jsonFromFile(assetPath);
    std::string texturePath = std::string(RESOURCES_PATH) + "textures/" +
                              std::string(jsonData["texturePath"]);

    float width = jsonData["frameSize"]["width"];
    float height = jsonData["frameSize"]["height"];

    auto texture = loadSprite(texturePath, renderer);
    _sprites[assetPath] = std::make_shared<sdl::Sprite>(std::move(texture),
                                                        Vec2({width, height}));
}
