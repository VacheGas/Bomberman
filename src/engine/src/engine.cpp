#include "engine/engine.hpp"
#include "engine/graphic_element.hpp"
#include "engine/generate_id.hpp"
#include "engine/sprite_factory.hpp"

#include <SDL3_image/SDL_image.h>
#include <memory>

namespace sdl {

bool Engine::_initialized = false;

Engine::Engine(std::string_view title, size_t width, size_t height, int flags)
    : _title{title}, _width{width}, _height{height}, _flags{flags} {

    auto errorMessage = "There can be only one instance of the engine";
    if (_initialized)
        throw std::runtime_error(errorMessage);
    _initialized = true;
    initSDL();
}

Engine::~Engine() {
    cleanSDL();
}

std::unique_ptr<Texture, SdlTextureDeleter> Engine::load(
    const std::string& assetPath) {
    SDL_Surface* tempSurface = IMG_Load(assetPath.c_str());
    std::unique_ptr<Texture, SdlTextureDeleter> texture(
        SDL_CreateTextureFromSurface(_renderer, tempSurface));
    SDL_DestroySurface(tempSurface);
    return texture;
}

void Engine::run() {
    SDL_Event e;
    while (e.type != SDL_EVENT_QUIT) {
        SDL_PollEvent(&e);
        update();
        draw(_renderer);
    }
}

std::size_t Engine::registerGraphicElement(std::string_view assetPath,
                                            Vec4 dstRect,
                                            size_t spriteRowCount,
                                            size_t spriteColCount) {
    _factory->addNewSprite(assetPath, _renderer, spriteRowCount, spriteColCount);
    const std::size_t elementId = sdl::generateGraphicElementID();
    _graphicElements[elementId] = std::make_unique<GraphicElement>(
        _factory->getSprite(assetPath), dstRect);
    return elementId;
}

void Engine::setDrawColor(SDL_Color color) {
    SDL_SetRenderDrawColor(_renderer, color.r, color.g, color.b, color.a);
}

void Engine::present() {
    SDL_RenderPresent(_renderer);
}

void Engine::clear() {
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
    SDL_RenderClear(_renderer);
}

size_t Engine::width() const {
    return _width;
}

size_t Engine::height() const {
    return _height;
}

void Engine::update() {
    for (auto it = _graphicElements.begin(); it != _graphicElements.end();
         ++it) {
        it->second->update();
    }
}

void Engine::draw(SDL_Renderer* renderer) {
    SDL_RenderClear(_renderer);
    SDL_SetRenderDrawColor(_renderer, 0, 100, 0, 255);
    for (auto it = _graphicElements.begin(); it != _graphicElements.end();
         ++it) {
        it->second->draw(renderer);
    }
    present();
}

void Engine::initSDL() {
    if (SDL_InitSubSystem(SDL_INIT_EVERYTHING) < 0) {
        throw std::runtime_error("SDL initialization error: " +
                                 std::string(SDL_GetError()));
    }

    _window = SDL_CreateWindow(_title.data(), _width, _height, _flags);

    if (!_window) {
        SDL_Quit();
        throw std::runtime_error("window creation error: " +
                                 std::string(SDL_GetError()));
    }
    _renderer = SDL_CreateRenderer(_window, nullptr, SDL_RENDERER_ACCELERATED);
    if (!_renderer) {
        SDL_DestroyWindow(_window);
        SDL_Quit();
        throw std::runtime_error("Renderer creation error : " +
                                 std::string(SDL_GetError()));
    }
}

void Engine::cleanSDL() {
    if (_renderer)
        SDL_DestroyRenderer(_renderer);
    if (_window)
        SDL_DestroyWindow(_window);
    SDL_Quit();
}

}  // namespace sdl