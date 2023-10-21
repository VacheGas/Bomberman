#include <gtest/gtest.h>
#include <engine/engine.hpp>

TEST(Engine, Animation) {
    sdl::Engine engine("Bomberman", 800, 640, 0);
    engine.registerAnimatableSprite("../assets/animation/anim3.png",
                                    SDL_FRect{0, 0, 256, 256},
                                    SDL_FRect{200, 200, 256, 256}, 6, 8, 0);
    engine.run();
}