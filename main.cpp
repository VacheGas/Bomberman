//
// Created by Vache Gasparyan on 16.09.23.
//

#include <core/game.hpp>

int main() {
    auto &game = sdl::Game::getInstance();
    game.init("Bomberman", 800, 640, 0);
    game.registerAnimatableObject(
        "../assets/animation/animate-alpha.png", "animal",
        SDL_FRect{0, 0, 128, 82}, SDL_Point{0, 0}, SDL_Point{0, 0},
        1, 6, 0);
    game.pollEvents();
}
