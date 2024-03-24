//
// Created by Vache Gasparyan on 23.03.24.
//

#ifndef BOMBERMAN_MENU_HPP
#define BOMBERMAN_MENU_HPP
#include <engine/engine.hpp>
#include <engine/graphic_element.hpp>
#include <engine/window.hpp>
#include <memory>

namespace components {

class Menu {
public:
    Menu();

public:
    void run();

private:
    std::shared_ptr<sdl::Window> _window =
        std::make_shared<sdl::Window>("Menu", 1000, 1000, 0);
    std::unique_ptr<sdl::Engine> _engine =
        std::make_unique<sdl::Engine>(_window);
    std::array<std::pair<std::size_t, std::shared_ptr<sdl::GraphicElement>>, 3>
        _elements;
};

}  // namespace components

#endif  //BOMBERMAN_MENU_HPP
