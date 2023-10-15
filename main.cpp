//
// Created by Vache Gasparyan on 16.09.23.
//

#include <core/game.hpp>

int main() {
    auto &game = sdl::Game::getInstance();
    game.init("Sample", 800, 640, 0);
    game.pollEvents();
}
