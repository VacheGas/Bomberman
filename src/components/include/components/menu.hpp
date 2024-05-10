//
// Created by Vache Gasparyan on 23.03.24.
//

#ifndef BOMBERMAN_MENU_HPP
#define BOMBERMAN_MENU_HPP
#include <engine/graphic_element.hpp>
#include <engine/window.hpp>
#include <memory>
#include "engine/drawing_context.hpp"

namespace components {

class Menu {
public:
    Menu();

public:
    void run();

private:
    void declareSprites();

private:
    std::shared_ptr<sdl::Window> _window =
        std::make_shared<sdl::Window>("Menu", 10000, 10000, 0);
    std::unique_ptr<sdl::DrawingContext> _engine =
        std::make_unique<sdl::DrawingContext>(_window);
    std::array<std::pair<std::size_t, std::shared_ptr<sdl::GraphicElement>>, 3>
        _elements;
};

}  // namespace components

#endif  //BOMBERMAN_MENU_HPP
