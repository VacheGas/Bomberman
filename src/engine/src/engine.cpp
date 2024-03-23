#include "engine/engine.hpp"
#include "engine/graphic_element.hpp"
#include "engine/sprite_factory.hpp"

#include <SDL3_image/SDL_image.h>
#include <memory>
#include <utility>

namespace sdl {

bool Engine::_initialized = false;

Engine::Engine(std::shared_ptr<Window> window) : _window(std::move(window)) {

    auto errorMessage = "There can be only one instance of the engine";
    if (_initialized)
        throw std::runtime_error(errorMessage);
    _initialized = true;
}

void Engine::registerGraphicElement(
    const std::shared_ptr<GraphicElement>& element, std::size_t elementId) {
    _graphicElements[elementId] = sdl::Texture(SDL_CreateTextureFromSurface(
        _window->renderer()->renderer().get(), element->data()));
}

void Engine::setDrawColor(SDL_Color color) {
    SDL_SetRenderDrawColor(_window->renderer()->renderer().get(), color.r,
                           color.g, color.b, color.a);
}
// TODO SDL_PumpEvents will be removed
void Engine::present() {
    SDL_PumpEvents();
    SDL_RenderPresent(_window->renderer()->renderer().get());
}

void Engine::clear() {
    SDL_RenderClear(_window->renderer()->renderer().get());
    SDL_SetRenderDrawColor(_window->renderer()->renderer().get(), 0, 0, 0, 255);
}

void Engine::handleInput() {
    _inputHandler.update();

    // Check if a specific key is pressed
    if (_inputHandler.isKeyPressed(SDL_SCANCODE_A)) {
        // TODO: move character
    }

    // Check if another key is pressed
    if (_inputHandler.isKeyPressed(SDL_SCANCODE_B)) {
        // TODO: move character
    }
}
// TODO instead of drawing its all time you can draw one time get surface and draw it instead
void Engine::draw(std::size_t elementID, const Vec4& srcRect,
                  const Vec4& dstRect) {
    if (_graphicElements.find(elementID) == _graphicElements.end()) {
        throw std::runtime_error("element not exist");
    }
    SDL_FRect src(srcRect[0], srcRect[1], srcRect[2], srcRect[3]);

    SDL_FRect dst(dstRect[0], dstRect[1], dstRect[2], dstRect[3]);
    SDL_RenderTexture(_window->renderer()->renderer().get(),
                      _graphicElements[elementID].get(), &src, &dst);
}

const std::shared_ptr<Window>& Engine::window() const {
    return _window;
}

}  // namespace sdl