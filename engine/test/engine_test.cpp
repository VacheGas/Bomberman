#include <gtest/gtest.h>

#include <engine/engine.hpp>

TEST(Engine, Animation) {
    sdl::Engine engine("Bomberman", 800, 640, 0);
    engine.registerAnimatableSprite("../assets/animation/anim3.png",
                                    {{0, 0, 256, 256}},
                                    {{200, 200, 256, 256}}, 6, 8);
    engine.run();
}