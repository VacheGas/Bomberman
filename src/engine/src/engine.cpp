#include "engine/engine.hpp"
#include "engine/animatable_graphic_element.hpp"
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
    bool quit = false;
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT)
                quit = true;
        }
        update();
        handleInput();
        draw(_renderer);
    }
}

std::size_t Engine::registerGraphicElement(std::string_view assetPath,
                                           Vec4 srcRect) {
    _factory->addNewSprite(assetPath, _renderer, srcRect);
    const std::size_t elementId = sdl::generateGraphicElementID();
    _graphicElements[elementId] = std::make_unique<GraphicElement>(
        _factory->getSprite(assetPath), srcRect);
    return elementId;
}

std::size_t Engine::registerAnimatableGraphicElement(std::string_view assetPath,
                                                     Vec4 srcRect,
                                                     size_t spriteRowCount,
                                                     size_t spriteColCount) {
    _factory->addNewAnimationSprite(assetPath, _renderer, srcRect,
                                    spriteRowCount, spriteColCount);
    const std::size_t elementId = sdl::generateGraphicElementID();
    _graphicElements[elementId] = std::make_unique<AnimatableGraphicElement>(
        _factory->getSprite(assetPath), srcRect, 1);
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

void Engine::handleInput() {
    _inputHandler.update();

    // Check if a specific key is pressed
    if (_inputHandler.isKeyPressed(SDL_SCANCODE_A)) {
        // Render a rectangle at position (100, 100) with width 50 and height 50
        SDL_FRect rect = {100, 100, 50, 50};
        SDL_SetRenderDrawColor(_renderer, 255, 0, 0, 255);  // Set color to red
        SDL_RenderFillRect(_renderer, &rect);
    }

    // Check if another key is pressed
    if (_inputHandler.isKeyPressed(SDL_SCANCODE_B)) {
        // Render a circle at position (200, 200) with radius 25
        int radius = 25;
        int centerX = 200;
        int centerY = 200;
        SDL_SetRenderDrawColor(_renderer, 0, 0, 255, 255);  // Set color to blue
        for (int x = -radius; x <= radius; x++) {
            for (int y = -radius; y <= radius; y++) {
                if (x * x + y * y <= radius * radius) {
                    SDL_RenderPoint(_renderer, centerX + x, centerY + y);
                }
            }
        }
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