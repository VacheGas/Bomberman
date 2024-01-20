#include "engine/engine.hpp"
#include "engine/animatable_graphic_element.hpp"
#include "engine/generate_id.hpp"
#include "engine/sprite_factory.hpp"

#include <SDL3_image/SDL_image.h>
#include <memory>

namespace sdl {

bool Engine::_initialized = false;

Engine::Engine(std::unique_ptr<Renderer> renderer) : _renderer(std::move(renderer)) {

    auto errorMessage = "There can be only one instance of the engine";
    if (_initialized)
        throw std::runtime_error(errorMessage);
    _initialized = true;
}

std::unique_ptr<Texture, SdlTextureDeleter> Engine::load(
    const std::string& assetPath) {
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

std::size_t Engine::registerGraphicElement(std::string_view assetPath,
                                           Vec4 srcRect) {
    _factory->addNewSprite(assetPath, _renderer->renderer().get(), srcRect);
    const std::size_t elementId = sdl::generateGraphicElementID();
    _graphicElements[elementId] = std::make_unique<GraphicElement>(
        _factory->getSprite(assetPath), srcRect);
    return elementId;
}

std::size_t Engine::registerAnimatableGraphicElement(std::string_view assetPath,
                                                     Vec4 srcRect,
                                                     size_t spriteRowCount,
                                                     size_t spriteColCount) {
    _factory->addNewAnimationSprite(assetPath, _renderer->renderer().get(), srcRect, spriteRowCount,
                                    spriteColCount);
    const std::size_t elementId = sdl::generateGraphicElementID();
    _graphicElements[elementId] = std::make_unique<AnimatableGraphicElement>(
        _factory->getSprite(assetPath), srcRect, 1);
    return elementId;
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
    for (auto it = _graphicElements.begin(); it != _graphicElements.end();
         ++it) {
        it->second->update();
    }
}

void Engine::draw(SDL_Renderer* renderer) {
    SDL_RenderClear(_renderer->renderer().get());
    SDL_SetRenderDrawColor(_renderer->renderer().get(), 0, 100, 0, 255);
    for (auto it = _graphicElements.begin(); it != _graphicElements.end();
         ++it) {
        it->second->draw(renderer);
    }
    present();
}

}  // namespace sdl