//
// Created by Vache Gasparyan on 17.12.23.
//

#pragma once

#include <string>
#include <unordered_map>
#include <unordered_set>

#include <SDL3_image/SDL_image.h>
#include <engine/vec.hpp>
#include <nlohmann/json.hpp>
#include "engine/sdlTextureDeleter.hpp"
#include "engine/sprite.hpp"

#include <fstream>

namespace sdl {
class Engine;
class Sprite;

class SpriteFactory {
public:
    SpriteFactory() = default;

public:
    [[nodiscard]] static std::size_t addNewSprite(const std::string_view& path);

    [[nodiscard]] static std::shared_ptr<sdl::Sprite> getSprite(
        const std::string_view& id);
    [[nodiscard]] static std::shared_ptr<sdl::Sprite> getSprite(std::size_t id);

private:
    static std::unordered_map<std::size_t, std::shared_ptr<Sprite>> _sprites;
    static std::unordered_map<std::string_view, std::size_t> _paths;
};

}  // namespace sdl
