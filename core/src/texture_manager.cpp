#include "texture_manager.hpp"
#include <SDL_image.h>

#include <iostream> // tbr

namespace sdl {

bool TextureManager::load(const std::string& fileName, 
                          const std::string& id,
                          SDL_Renderer* pRenderer) {
    SDL_Surface* pTempSurface = IMG_Load(fileName.c_str());
    if (pTempSurface == 0) {
        return false;
    }
    SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer, pTempSurface);
    SDL_DestroySurface(pTempSurface);
    if (pTexture != 0) {
        _textures[id] = pTexture;
        return true;
    }
    return false;
}

void TextureManager::draw(const std::string& id, 
                          SDL_Renderer* pRenderer, 
                          SDL_FRect dstRect,
                          size_t currentRow, 
                          size_t currentCol,
                          SDL_RendererFlip flip) {
    SDL_FRect srcRect;
    srcRect.x = dstRect.w * currentCol;
    srcRect.y = dstRect.h * currentRow;
    srcRect.w = dstRect.w;
    srcRect.h = dstRect.h;
    SDL_RenderTextureRotated(pRenderer, _textures[id], &srcRect, &dstRect, 0, 0, flip);
}

void TextureManager::clearTexture(const std::string& id) {
    _textures.erase(id);
}

} // namesapce sdl