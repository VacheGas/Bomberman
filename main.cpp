//
// Created by Vache Gasparyan on 16.09.23.
//

#include <core/game.hpp>

int main() {
    auto &game = sdl::Game::getInstance();
    game.init("Bomberman", 800, 640, 0);
    game.registerAnimatableObject(
        "../assets/animation/anim2.png",
        SDL_FRect{0, 0, 192, 192}, 
        SDL_FRect{100, 100, 192, 192}, 
        SDL_Point{0, 0}, 
        SDL_Point{0, 0},
        4, 5, 0);
    game.pollEvents();
}
