#include "game.hpp"
#include "exception.hpp"

#include <iostream>  // tbr

namespace sdl {

bool Game::_initialized{};

void Game::init(const std::string& title, size_t width, size_t height, int flags) {

    if (_initialized) 
        throw SDLException("The engine is already initialized");
    _initialized = true;

    initSDL(title, width, height, flags);
    initObjects();
}

Game::~Game() {
    cleanObjects();
    cleanSDL();
}

Game& Game::getInstance() {
    static Game _instance;
    return _instance;
}

void Game::pollEvents() {
    SDL_Event e;
    bool quit = false;
    while (quit == false) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) quit = true;
            update();
            draw(_renderer);
            // SDL_Delay(50);
        }
    }
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
    SDL_SetRenderDrawColor(_renderer, 0, 100, 100, 255);
    for (auto object : _objects) {
        object->draw(renderer);
    }
    present();
}

void Game::initSDL(const std::string& title, size_t width, size_t height, int flags) {
    if (SDL_InitSubSystem(SDL_INIT_EVERYTHING) < 0) {
        throw SDLException("SDL initialization error: " +
                           std::string(SDL_GetError()));
    }

    _width = width;
    _height = height;
    _window = SDL_CreateWindow(title.c_str(), _width, _height, flags);

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

void Game::initObjects() {
    _textureManager.load("../assets/animation/animate-alpha.png", "animal", _renderer);

    _objects.push_back(new AnimatableGameObject(
        _textureManager, SDL_FRect{0, 0, 128, 82}, "animal", SDL_Point{0, 0},
        SDL_Point{0, 0}, 1, 6, 0));
}

void Game::cleanSDL() {
    if (_renderer)
        SDL_DestroyRenderer(_renderer);
    if (_window)
        SDL_DestroyWindow(_window);
    SDL_Quit();
}

void Game::cleanObjects() {
    for (auto object : _objects) {
        delete object;
    }
}

}  // namespace sdl