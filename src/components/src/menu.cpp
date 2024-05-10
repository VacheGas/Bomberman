//
// Created by Vache Gasparyan on 23.03.24.
//

#include <components/menu.hpp>
#include "engine/drawing_context.hpp"

components::Menu::Menu() {
    declareSprites();
}

void components::Menu::run() {
    while (true) {
        _engine->drawImage(_elements[0].first, _elements[0].second->srcRect(),
                           _elements[0].second->dstRect());
        _engine->drawImage(_elements[1].first, _elements[1].second->srcRect(),
                           _elements[1].second->dstRect());
        _engine->present();
        _engine->clear();
    }
}

void components::Menu::declareSprites() {
    _elements[0].first = sdl::SpriteFactory::addNewSprite(
        RESOURCES_PATH "json/button_play.json");
    _elements[0].second = std::make_shared<sdl::GraphicElement>(
        sdl::SpriteFactory::getSprite(_elements[0].first),
        Vec4({100, 100, 134, 61}));

    _elements[1].first = sdl::SpriteFactory::addNewSprite(
        RESOURCES_PATH "json/button_load-map.json");
    _elements[1].second = std::make_shared<sdl::GraphicElement>(
        sdl::SpriteFactory::getSprite(_elements[1].first),
        Vec4({100, 400, 134, 61}));

    _engine->registerSprite(_elements[0].second->sprite(), _elements[0].first);
    _engine->registerSprite(_elements[1].second->sprite(), _elements[1].first);
}
