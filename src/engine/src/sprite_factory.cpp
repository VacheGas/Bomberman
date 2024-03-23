//
// Created by Vache Gasparyan on 17.12.23.
//

#include "engine/sprite_factory.hpp"
#include <engine/generate_id.hpp>
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

}  // namespace
std::unordered_map<std::size_t, std::shared_ptr<sdl::Sprite>>
    sdl::SpriteFactory::_sprites;
std::unordered_map<std::string_view, std::size_t> sdl::SpriteFactory::_paths;

std::shared_ptr<sdl::Sprite> sdl::SpriteFactory::getSprite(
    const std::string_view& id) {
    if (_paths.contains(id))
        return _sprites[_paths[id]];
    return nullptr;
}

std::shared_ptr<sdl::Sprite> sdl::SpriteFactory::getSprite(std::size_t id) {
    if (_sprites.contains(id))
        return _sprites[id];
    return nullptr;
}

std::size_t sdl::SpriteFactory::addNewSprite(
    const std::string_view& assetPath) {
    if (_paths.contains(assetPath))
        return _paths[assetPath];

    nlohmann::json jsonData = jsonFromFile(assetPath);
    std::string texturePath = std::string(RESOURCES_PATH) + "textures/" +
                              std::string(jsonData["texturePath"]);

    float width = jsonData["frameSize"]["width"];
    float height = jsonData["frameSize"]["height"];
    std::size_t id = generateGraphicElementID();
    _sprites[id] = std::make_shared<sdl::Sprite>(
        std::unique_ptr<SDL_Surface, sdl::SdlSurfaceDeleter>(
            IMG_Load(texturePath.data())),
        Vec2({width, height}));
    _paths.insert({assetPath, id});
    return id;
}
