#include "engine/drawing_context.hpp"
#include "engine/graphic_element.hpp"
#include "engine/sprite_factory.hpp"

#include <SDL3_image/SDL_image.h>
#include <memory>
#include <utility>

namespace sdl {

bool DrawingContext::_initialized = false;
// TODO poxel anun@ drawing_context
DrawingContext::DrawingContext(std::shared_ptr<Window> window)
    : _window(std::move(window)) {
    auto errorMessage = "There can be only one instance of the engine";
    if (_initialized)
        throw std::runtime_error(errorMessage);
    _initialized = true;
}

void DrawingContext::registerSprite(const std::shared_ptr<sdl::Sprite>& element,
                                    std::size_t elementId) {
    _graphicElements[elementId] = sdl::Texture(SDL_CreateTextureFromSurface(
        _window->renderer()->renderer().get(), element->data()));
}

void DrawingContext::drawColor(SDL_Color color) {
    SDL_SetRenderDrawColor(_window->renderer()->renderer().get(), color.r,
                           color.g, color.b, color.a);
}
// TODO SDL_PumpEvents will be removed
void DrawingContext::present() {
    SDL_PumpEvents();
    SDL_RenderPresent(_window->renderer()->renderer().get());
}

void DrawingContext::clear() {
    SDL_RenderClear(_window->renderer()->renderer().get());
    SDL_SetRenderDrawColor(_window->renderer()->renderer().get(), 0, 0, 0, 255);
}

void DrawingContext::handleInput() {
    _inputHandler.update();

    // Check if a specific key is pressed
    if (_inputHandler.isKeyPressed(ENGINE_SCANCODES::A)) {
        // TODO: move character
    }

    // Check if another key is pressed
    if (_inputHandler.isKeyPressed(ENGINE_SCANCODES::W)) {
        // TODO: move character
    }
}
// TODO change Vec names
// TODO instead of drawing its all time you can draw one time get surface and draw it instead
void DrawingContext::drawImage(std::size_t elementID, const Vec4& srcRect,
                               const Vec4& dstRect) {
    if (_graphicElements.find(elementID) == _graphicElements.end()) {
        throw std::runtime_error("element not exist");
    }
    SDL_FRect src;
    SDL_FRect dst;
    src.x = srcRect[0];
    src.y = srcRect[1];
    src.w = srcRect[2];
    src.h = srcRect[3];
    dst.x = dstRect[0];
    dst.y = dstRect[1];
    dst.w = dstRect[2];
    dst.h = dstRect[3];
    SDL_RenderTexture(_window->renderer()->renderer().get(),
                      _graphicElements[elementID].get(), &src, &dst);
}

const std::shared_ptr<Window>& DrawingContext::window() const {
    return _window;
}

}  // namespace sdl