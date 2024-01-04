#include <engine/engine.hpp>

#include <memory>

#include <SDL3_image/SDL_image.h>

namespace sdl {

bool Engine::_initialized = false;

Engine::Engine(std::unique_ptr<Renderer> renderer) : _renderer(std::move(renderer)) {

    auto errorMessage = "There can be only one instance of the engine";
    if (_initialized)
        throw std::runtime_error(errorMessage);
    _initialized = true;
}

std::unique_ptr<Texture, SdlTextureDeleter> Engine::load(const std::string& assetPath) {
    SDL_Surface* tempSurface = IMG_Load(assetPath.c_str());
    std::unique_ptr<Texture, SdlTextureDeleter> texture(SDL_CreateTextureFromSurface(_renderer->renderer().get(), tempSurface));
    SDL_DestroySurface(tempSurface);
    return texture;
}

void Engine::run() {
    SDL_Event e;
    bool quit = false;
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT)
                quit = true;
        }
        update();
        draw(_renderer->renderer().get());
    }
}

void Engine::registerSprite(const std::string& assetPath,
                            Vec4 srcRect, Vec4 dstRect) {
    auto sdlSrcRect = SDL_FRect{srcRect[0], srcRect[1], srcRect[2], srcRect[3]};
    auto sdlDstRect = SDL_FRect{dstRect[0], dstRect[1], dstRect[2], dstRect[3]};
    _sprites[assetPath] = std::make_unique<Sprite>(load(assetPath), sdlSrcRect, sdlDstRect);
}

void Engine::registerAnimatableSprite(const std::string& assetPath,
                                      Vec4 srcRect,
                                      Vec4 dstRect, size_t spriteRowCount,
                                      size_t spriteColCount,
                                      size_t animationSpeed) {
    auto sdlSrcRect = SDL_FRect{srcRect[0], srcRect[1], srcRect[2], srcRect[3]};
    auto sdlDstRect = SDL_FRect{dstRect[0], dstRect[1], dstRect[2], dstRect[3]};
    _sprites[assetPath] = std::make_unique<AnimatableSprite>(load(assetPath), sdlSrcRect,
                                            sdlDstRect, spriteRowCount,
                                            spriteColCount, animationSpeed);
}

void Engine::setDrawColor(SDL_Color color) {
    SDL_SetRenderDrawColor(_renderer->renderer().get(), color.r, color.g, color.b, color.a);
}

void Engine::present() {
    SDL_RenderPresent(_renderer->renderer().get());
}

void Engine::clear() {
    SDL_SetRenderDrawColor(_renderer->renderer().get(), 0, 0, 0, 255);
    SDL_RenderClear(_renderer->renderer().get());
}


void Engine::update() {
    for (auto it = _sprites.begin(); it != _sprites.end(); ++it) {
        it->second->update();
    }
}

void Engine::draw(SDL_Renderer* renderer) {
    SDL_RenderClear(_renderer->renderer().get());
    SDL_SetRenderDrawColor(_renderer->renderer().get(), 0, 100, 0, 255);
    for (auto & _sprite : _sprites) {
        _sprite.second->render(renderer);
    }
    present();
}

}  // namespace sdl