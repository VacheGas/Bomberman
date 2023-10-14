//
// Created by Vache Gasparyan on 16.09.23.
//

#include <core/game.hpp>

int main() {
    auto &engine = sdl::Engine::getInstance();
    engine.init("Sample", 800, 640, 0);
    engine.pollEvents();
}
