#include "test_utils/gtest_main.hpp"

#include "engine/engine.hpp"

TEST(Engine, Animation) {
    // TODO: Add future of 'UI' testing with stored textures per frame
    sdl::Engine engine("Bomberman", 800, 640, 0);
    engine.registerGraphicElement(std::string(RESOURCES_PATH "json/explosion_1.json"), {{0, 0, 256, 256}});
    engine.run();
}