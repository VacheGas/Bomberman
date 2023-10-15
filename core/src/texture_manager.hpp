#pragma once

#include <SDL.h>
#include <unordered_map>
#include <string>

namespace sdl {

class TextureManager {
public:
    TextureManager() = default;

public:
    bool load(const std::string& assetPath,
              SDL_Renderer* renderer);

    void draw(const std::string& assetPath, 
              SDL_Renderer* renderer, 
              SDL_FRect dstRect,
              size_t currentRow = 0, 
              size_t currentCol = 0,
              SDL_RendererFlip flip = SDL_FLIP_NONE);

    void clearTexture(const std::string& assetPath);

private:
    std::unordered_map<std::string, SDL_Texture*> _textures;
};

} // namespace sdl