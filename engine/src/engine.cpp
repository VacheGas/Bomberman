#include <engine/engine.hpp>

#include <SDL_image.h>

namespace sdl {

bool Engine::_initialized{};

void Engine::init(const std::string& title, size_t width, size_t height,
                  int flags) {
    _title = title;
    _width = width;
    _height = height;
    _SDLFlags = flags;

    if (_initialized)
        throw std::runtime_error("The engine is already initialized");
    _initialized = true;

    initSDL();
}

Engine::~Engine() {
    cleanObjects();
    cleanSDL();
}

Engine& Engine::getInstance() {
    static Engine _instance;
    return _instance;
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

void Engine::registerObject(const std::string& assetPath,
                            SDL_FRect initialSrcRect, SDL_FRect dstRect) {
    load(assetPath);
    _objects.push_back(new Sprite(_textures[assetPath], initialSrcRect, dstRect));
}

void Engine::registerAnimatableObject(
    const std::string& assetPath, SDL_FRect initialSrcRect, SDL_FRect dstRect,
    SDL_Point initialVelocity, SDL_Point initialAcceleration,
    size_t spriteRowCount, size_t spriteColCount, size_t animationSpeed) {
    load(assetPath);
    _objects.push_back(
        new AnimatableSprite(_textures[assetPath], initialSrcRect, dstRect,
                             initialVelocity, initialAcceleration, animationSpeed,
                             spriteRowCount, spriteColCount));
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
    for (auto object : _objects) {
        object->update();
    }
}

void Engine::draw(SDL_Renderer* renderer) {
    SDL_RenderClear(_renderer);
    SDL_SetRenderDrawColor(_renderer, 0, 100, 0, 255);
    for (auto object : _objects) {
        object->render(renderer);
    }
    present();
}

void Engine::initSDL() {
    if (SDL_InitSubSystem(SDL_INIT_EVERYTHING) < 0) {
        throw std::runtime_error("SDL initialization error: " +
                                 std::string(SDL_GetError()));
    }

    _window = SDL_CreateWindow(_title.c_str(), _width, _height, _SDLFlags);

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
    _initialized = false;
}

void Engine::cleanObjects() {
    for (auto object : _objects) {
        delete object;
    }
}

void Engine::cleanTextures() {
    for (auto texture : _textures) {
        SDL_DestroyTexture(_textures[texture.first]);
        _textures.erase(texture.first);
    }
}

}  // namespace sdl