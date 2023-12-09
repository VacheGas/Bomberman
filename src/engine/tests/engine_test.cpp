#include "test_utils/gtest_main.hpp"

#include "engine/include/engine/engine.hpp"


TEST(Engine, Animation) {
    // TODO: Add future of 'UI' testing with stored textures per frame
    sdl::Engine engine("Bomberman", 800, 640, 0);
    engine.registerAnimatableSprite(RESOURCES_PATH "/animation/anim3.png",
                                    {{0, 0, 256, 256}},
                                    {{200, 200, 256, 256}}, 6, 8);
    engine.run();
}