#include "game.hpp"
#include "exception.hpp"

namespace sdl {

bool Game::_initialized{};

void Game::init(const std::string& title, size_t width, size_t height,
                int flags) {
    _title = title;
    _width = width;
    _height = height;
    _SDLFlags = flags;

    if (_initialized)
        throw SDLException("The engine is already initialized");
    _initialized = true;

    initSDL();
}

Game::~Game() {
    cleanObjects();
    cleanSDL();
}

Game& Game::getInstance() {
    static Game _instance;
    return _instance;
}

void Game::run() {
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

void Game::registerObject(const std::string& assetPath,
                          SDL_FRect initialSrcRect, SDL_FRect dstRect) {
    _textureManager.load(assetPath, _renderer);
    _objects.push_back(
        new GameObject(_textureManager, initialSrcRect, dstRect, assetPath));
}

void Game::registerAnimatableObject(
    const std::string& assetPath, SDL_FRect initialSrcRect, SDL_FRect dstRect,
    SDL_Point initialVelocity, SDL_Point initialAcceleration,
    size_t spriteRowCount, size_t spriteColCount, size_t animationSpeed) {
    _textureManager.load(assetPath, _renderer);
    _objects.push_back(new AnimatableGameObject(
        _textureManager, initialSrcRect, dstRect, assetPath, initialVelocity,
        initialAcceleration, spriteRowCount, spriteColCount, animationSpeed));
}

void Game::setDrawColor(SDL_Color color) {
    SDL_SetRenderDrawColor(_renderer, color.r, color.g, color.b, color.a);
}

void Game::present() {
    SDL_RenderPresent(_renderer);
}

void Game::clear() {
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
    SDL_RenderClear(_renderer);
}

size_t Game::width() const {
    return _width;
}

size_t Game::height() const {
    return _height;
}

void Game::update() {
    for (auto object : _objects) {
        object->update();
    }
}

void Game::draw(SDL_Renderer* renderer) {
    SDL_RenderClear(_renderer);
    SDL_SetRenderDrawColor(_renderer, 0, 100, 0, 255);
    for (auto object : _objects) {
        object->draw(renderer);
    }
    present();
}

void Game::initSDL() {
    if (SDL_InitSubSystem(SDL_INIT_EVERYTHING) < 0) {
        throw SDLException("SDL initialization error: " +
                           std::string(SDL_GetError()));
    }

    _window = SDL_CreateWindow(_title.c_str(), _width, _height, _SDLFlags);

    if (!_window) {
        SDL_Quit();
        throw SDLException("window creation error: " +
                           std::string(SDL_GetError()));
    }
    _renderer = SDL_CreateRenderer(_window, nullptr, SDL_RENDERER_ACCELERATED);
    if (!_renderer) {
        SDL_DestroyWindow(_window);
        SDL_Quit();
        throw SDLException("Renderer creation error : " +
                           std::string(SDL_GetError()));
    }
}

void Game::cleanSDL() {
    if (_renderer)
        SDL_DestroyRenderer(_renderer);
    if (_window)
        SDL_DestroyWindow(_window);
    SDL_Quit();
    _initialized = false;
}

void Game::cleanObjects() {
    for (auto object : _objects) {
        delete object;
    }
}

}  // namespace sdl