#include <gtest/gtest.h>
#include <engine/engine.hpp>

TEST(Engine, Animation) {
    auto& engine = sdl::Engine::getInstance();
    engine.init("Bomberman", 800, 640, 0);
    engine.registerAnimatableObject("../assets/animation/anim3.png",
                                    SDL_FRect{0, 0, 256, 256},
                                    SDL_FRect{300, 300, 256, 256},
                                    SDL_Point{0, 0}, SDL_Point{0, 0}, 6, 8, 0);
    engine.run();
}