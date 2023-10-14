#pragma once

#include <SDL.h>
#include <map>
#include <string>

class TextureManager {
public:
 TextureManager() = default;

public:
    bool load(const std::string& fileName, const std::string& id,
              SDL_Renderer* pRenderer);

    void draw(const std::string& id, SDL_Renderer* pRenderer, SDL_FRect dstRect,
              size_t currentRow = 0, size_t currentCol = 0,
              SDL_RendererFlip flip = SDL_FLIP_NONE);

    void clearTexture(const std::string& id);

private:
    std::map<std::string, SDL_Texture*> _textures;

};