//
// Created by Vache Gasparyan on 25.02.24.
//

#pragma once

#include <engine/engine.hpp>
#include <engine/graphic_element.hpp>
#include <memory>
#include <utility>

namespace components {
class Menu {
public:
    Menu();

private:
    std::shared_ptr<sdl::Window> _window = nullptr;
    std::array<std::pair<std::size_t, std::shared_ptr<sdl::GraphicElement>>, 2>
        _graphicElements;
};
}  // namespace components
