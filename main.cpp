//
// Created by Vache Gasparyan on 16.09.23.
//

#include <components/menu.hpp>

int main() {
    sdl::Window window = sdl::Window("Bomberman", 800, 640, 0);
    sdl::Engine engine(std::make_unique<sdl::Window>(std::move(window)));
    auto menuBomberman = components::Menu(engine.window());
    menuBomberman.createMainMenu();
}
