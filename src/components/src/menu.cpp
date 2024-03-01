//
// Created by Vache Gasparyan on 25.02.24.
//

#include "components/menu.hpp"
#include "engine/generate_id.hpp"

components::Menu::Menu(const std::shared_ptr<sdl::Window>& window)
    : _window(window) {}

void components::Menu::createMainMenu() {
    _menuWasOpen = true;
    std::array<std::string_view, 2> paths{
        {RESOURCES_PATH "json/button_load-map.json",
         RESOURCES_PATH "json/button_load-map.json"}};
    std::for_each(std::cbegin(paths), std::cend(paths), [this](const auto& it) {
        sdl::SpriteFactory::addNewSprite(it,
                                         _window->renderer()->renderer().get());
    });
    std::transform(
        std::cbegin(paths), std::cend(paths), std::begin(_graphicElements),
        [](const std::string_view& it) {
            return std::pair(sdl::generateGraphicElementID(),
                             std::make_shared<sdl::GraphicElement>(
                                 sdl::SpriteFactory::getSprite(it), {{0.0}}));
        });
    sdl::GraphicElement(sdl::SpriteFactory::getSprite("asd"), {{0.0}});
}

std::size_t components::Menu::addWidget(std::string_view path,
                                        const Vec2& dstRect) {
    sdl::SpriteFactory::addNewSprite(path,
                                     _window->renderer()->renderer().get());
    const std::size_t elementId = sdl::generateGraphicElementID();
    _graphicElements[elementId] = std::make_shared<sdl::GraphicElement>(
        sdl::SpriteFactory::getSprite(path), dstRect);
    return 1;
}

bool components::Menu::isMenuWasOpen() const {
    return _menuWasOpen;
}
