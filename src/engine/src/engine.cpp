#include <engine/engine.hpp>

#include <SDL3_image/SDL_image.h>

namespace sdl {

bool Engine::_initialized = false;

Engine::Engine(const std::string& title, size_t width, size_t height, int flags)
    : _title{title}, _width{width}, _height{height}, _flags{flags} {

    auto errorMessage = "There can be only one instance of the engine";
    if (_initialized)
        throw std::runtime_error(errorMessage);
    _initialized = true;
    initSDL();
}

Engine::~Engine() {
    cleanSprites();
    cleanSDL();
}

bool Engine::load(const std::string& assetPath) {
    SDL_Surface* tempSurface = IMG_Load(assetPath.c_str());
    if (tempSurface == 0) {
        return false;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(_renderer, tempSurface);
    SDL_DestroySurface(tempSurface);
    if (texture != 0) {
        _textures[assetPath] = texture;
        return true;
    }
    return false;
}

void Engine::run() {
    SDL_Event e;
    bool quit = false;
    while (quit == false) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT)
                quit = true;
        }
        update();
        draw(_renderer);
    }
}

void Engine::registerSprite(const std::string& assetPath,
                            Vec4 srcRect, Vec4 dstRect) {
    load(assetPath);
    auto sdlSrcRect = SDL_FRect{srcRect[0], srcRect[1], srcRect[2], srcRect[3]};
    auto sdlDstRect = SDL_FRect{dstRect[0], dstRect[1], dstRect[2], dstRect[3]};
    _sprites.push_back(
        new Sprite(_textures[assetPath], sdlSrcRect, sdlDstRect));
}

void Engine::registerAnimatableSprite(const std::string& assetPath,
                                      Vec4 srcRect,
                                      Vec4 dstRect, size_t spriteRowCount,
                                      size_t spriteColCount,
                                      size_t animationSpeed) {
    load(assetPath);
    auto sdlSrcRect = SDL_FRect{srcRect[0], srcRect[1], srcRect[2], srcRect[3]};
    auto sdlDstRect = SDL_FRect{dstRect[0], dstRect[1], dstRect[2], dstRect[3]};
    _sprites.push_back(new AnimatableSprite(_textures[assetPath], sdlSrcRect,
                                            sdlDstRect, spriteRowCount,
                                            spriteColCount, animationSpeed));
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
    for (auto sprite : _sprites) {
        sprite->update();
    }
}

void Engine::handleInput() {
    _inputHandler.update();

    // Check if a specific key is pressed
    if (_inputHandler.isKeyPressed(SDL_SCANCODE_A)) {
        // Render a rectangle at position (100, 100) with width 50 and height 50
        SDL_FRect rect = {100, 100, 50, 50};
        SDL_SetRenderDrawColor(_renderer, 255, 0, 0, 255); // Set color to red
        SDL_RenderFillRect(_renderer, &rect);
    }

    // Check if another key is pressed
    if (_inputHandler.isKeyPressed(SDL_SCANCODE_B)) {
        // Render a circle at position (200, 200) with radius 25
        int radius = 25;
        int centerX = 200;
        int centerY = 200;
        SDL_SetRenderDrawColor(_renderer, 0, 0, 255, 255); // Set color to blue
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
    for (auto sprite : _sprites) {
        sprite->render(renderer);
    }
    present();
}

void Engine::initSDL() {
    if (SDL_InitSubSystem(SDL_INIT_EVERYTHING) < 0) {
        throw std::runtime_error("SDL initialization error: " +
                                 std::string(SDL_GetError()));
    }

    _window = SDL_CreateWindow(_title.c_str(), _width, _height, _flags);

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

void Engine::cleanSprites() {
    for (auto sprite : _sprites) {
        delete sprite;
    }
}

void Engine::cleanTextures() {
    for (auto texture : _textures) {
        SDL_DestroyTexture(_textures[texture.first]);
        _textures.erase(texture.first);
    }
}

}  // namespace sdl