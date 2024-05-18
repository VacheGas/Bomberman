//
// Created by Vache Gasparyan on 23.03.24.
//

#include <components/menu.hpp>
#include <engine/drawing_context.hpp>

components::Menu::Menu() {
    declareSprites();
}

void components::Menu::run() {
    _subscribeID[0] = InputHandlerPublisher::subscribe(
        sdl::ENGINE_SCANCODES::W, [&]() { _state = STATE_SCANCODE::UP; });
    _subscribeID[1] = InputHandlerPublisher::subscribe(
        sdl::ENGINE_SCANCODES::S, [&]() { _state = STATE_SCANCODE::DOWN; });
    while (true) {
        if (_state == STATE_SCANCODE::UP) {
            _engine->drawImage(_elements[1].first,
                               _elements[1].second->srcRect(),
                               _elements[1].second->dstRect());
            _engine->drawImage(_elements[2].first,
                               _elements[2].second->srcRect(),
                               _elements[2].second->dstRect());
        } else if (_state == STATE_SCANCODE::DOWN) {
            _engine->drawImage(_elements[0].first,
                               _elements[0].second->srcRect(),
                               _elements[0].second->dstRect());
            _engine->drawImage(_elements[3].first,
                               _elements[3].second->srcRect(),
                               _elements[3].second->dstRect());
        } else {
            _engine->drawImage(_elements[0].first,
                               _elements[0].second->srcRect(),
                               _elements[0].second->dstRect());
            _engine->drawImage(_elements[2].first,
                               _elements[2].second->srcRect(),
                               _elements[2].second->dstRect());
        }
        _engine->present();
        _engine->clear();
        components::InputHandlerPublisher::monitoringInputHandler();
    }
}

void components::Menu::declareSprites() {
    _elements[0].first = sdl::SpriteFactory::addNewSprite(
        RESOURCES_PATH "json/button_play.json");
    _elements[0].second = std::make_shared<sdl::GraphicElement>(
        sdl::SpriteFactory::getSprite(_elements[0].first),
        Vec4({100, 100, 134, 61}));

    _elements[1].first = sdl::SpriteFactory::addNewSprite(
        RESOURCES_PATH "json/selectedPlay.json");
    _elements[1].second = std::make_shared<sdl::GraphicElement>(
        sdl::SpriteFactory::getSprite(_elements[1].first),
        Vec4({100, 100, 134, 61}));

    _elements[2].first = sdl::SpriteFactory::addNewSprite(
        RESOURCES_PATH "json/button_load-map.json");
    _elements[2].second = std::make_shared<sdl::GraphicElement>(
        sdl::SpriteFactory::getSprite(_elements[2].first),
        Vec4({100, 400, 134, 61}));

    _elements[3].first = sdl::SpriteFactory::addNewSprite(
        RESOURCES_PATH "json/selected_load-map.json");
    _elements[3].second = std::make_shared<sdl::GraphicElement>(
        sdl::SpriteFactory::getSprite(_elements[3].first),
        Vec4({100, 400, 134, 61}));

    _engine->registerSprite(_elements[0].second->sprite(), _elements[0].first);
    _engine->registerSprite(_elements[1].second->sprite(), _elements[1].first);
    _engine->registerSprite(_elements[2].second->sprite(), _elements[2].first);
    _engine->registerSprite(_elements[3].second->sprite(), _elements[3].first);
}
