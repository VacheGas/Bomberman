#include "test_utils/gtest_main.hpp"

#include "engine/engine.hpp"

TEST(Engine, Animation) {
    // TODO: Add future of 'UI' testing with stored textures per frame
    std::unique_ptr<sdl::Window> window = sdl::Window::createWindow(0, 800, 640, "Bomberman");
    std::unique_ptr<sdl::Renderer> renderer = sdl::Renderer::createRenderer(std::move(window));
    sdl::Engine engine(std::move(renderer));
    engine.registerAnimatableGraphicElement(std::string(RESOURCES_PATH "/animation/anim3.png"),
                                    {{0, 0, 256, 256}}, 6, 8);
    engine.run();
}