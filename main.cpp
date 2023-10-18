//
// Created by Vache Gasparyan on 16.09.23.
//

#include <core/game.hpp>

int main() {
    {
        auto& game = sdl::Game::getInstance();
        game.init("Bomberman", 800, 640, 0);
        game.registerAnimatableObject("../assets/animation/anim3.png",
                                    SDL_FRect{0, 0, 256, 256},
                                    SDL_FRect{300, 300, 256, 256},
                                    SDL_Point{0, 0}, SDL_Point{0, 0}, 6, 8, 0);
        game.run();
    }
}
