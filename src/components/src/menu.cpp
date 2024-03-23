//
// Created by Vache Gasparyan on 25.02.24.
//

#include "components/menu.hpp"
#include <engine/input_handler.hpp>
#include <iostream>
components::Menu::Menu() {
    _window = std::make_shared<sdl::Window>("menu", 800, 640, 0);
    sdl::Engine engine = sdl::Engine(_window);
    std::size_t id = sdl::SpriteFactory::addNewSprite(RESOURCES_PATH
                                                      "json/button_play.json");
    auto img = std::make_shared<sdl::GraphicElement>(
        sdl::SpriteFactory::getSprite(id), Vec4({0, 0, 256, 256}));
    engine.registerGraphicElement(img, id);
    while (true) {
        engine.clear();
        engine.draw(id, img->srcRect(), img->dstRect());
        engine.present();
        img->update();
    }
}
