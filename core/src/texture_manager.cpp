#include "texture_manager.hpp"
#include <SDL_image.h>

#include <iostream> // tbr

namespace sdl {

bool TextureManager::load(const std::string& assetPath,
                          SDL_Renderer* renderer) {
    SDL_Surface* tempSurface = IMG_Load(assetPath.c_str());
    if (tempSurface == 0) {
        return false;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
    SDL_DestroySurface(tempSurface);
    if (texture != 0) {
        _textures[assetPath] = texture;
        return true;
    }
    return false;
}

void TextureManager::draw(const std::string& id, 
                          SDL_Renderer* renderer, 
                          SDL_FRect dstRect,
                          size_t currentRow, 
                          size_t currentCol,
                          SDL_RendererFlip flip) {
    SDL_FRect srcRect;
    srcRect.x = dstRect.w * currentCol;
    srcRect.y = dstRect.h * currentRow;
    srcRect.w = dstRect.w;
    srcRect.h = dstRect.h;
    SDL_RenderTextureRotated(renderer, _textures[id], &srcRect, &dstRect, 0, 0, flip);
}

void TextureManager::clearTexture(const std::string& id) {
    _textures.erase(id);
}

} // namesapce sdl