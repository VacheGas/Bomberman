#include "texture_manager.hpp"
#include <SDL_image.h>

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
                          SDL_FRect initialSrcRect,
                          SDL_FRect dstRect,
                          size_t currentRow, 
                          size_t currentCol,
                          SDL_RendererFlip flip) {
    SDL_FRect filalSrcRect;
    filalSrcRect.x = initialSrcRect.w * currentCol;
    filalSrcRect.y = initialSrcRect.h * currentRow;
    filalSrcRect.w = initialSrcRect.w;
    filalSrcRect.h = initialSrcRect.h;
    SDL_RenderTextureRotated(renderer, _textures[id], &filalSrcRect, &dstRect, 0, 0, flip);
}

void TextureManager::clearTexture(const std::string& assetPath) {
    _textures.erase(assetPath);
}

} // namesapce sdl