#include "game.hpp"
#include "exception.hpp"

namespace sdl {

bool Engine::_initialized{};

void Engine::init(const std::string& title, size_t width, size_t height, int flags) {

    if (_initialized) {
        throw SDLException("The engine is already initialized");
    }

    _initialized = true;

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

Engine::~Engine() {
    if (_renderer)
        SDL_DestroyRenderer(_renderer);
    if (_window)
        SDL_DestroyWindow(_window);
    SDL_Quit();
}

Engine& Engine::getInstance() {
    static Engine _instance;
    return _instance;
}

void Engine::pollEvents() {
    SDL_Event e;
    bool quit = false;
    while (quit == false) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT)
                quit = true;
        }
    }
}

void Engine::setDrawColor(Color color) {
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

}  // namespace sdl