#include "test_utils/gtest_main.hpp"

#include "engine/engine.hpp"

TEST(Engine, Animation) {
    std::size_t id = sdl::SpriteFactory::addNewSprite(RESOURCES_PATH
                                                      "json/button_play.json");
    std::shared_ptr<sdl::Sprite> sprite = sdl::SpriteFactory::getSprite(id);
    auto img =
        std::make_shared<sdl::GraphicElement>(sprite, Vec4({0, 0, 256, 256}));
    auto window = std::make_shared<sdl::Window>("menu", sprite->height(),
                                                sprite->width(), 0);
    sdl::Engine engine = sdl::Engine(window);
    engine.registerGraphicElement(img, id);
    engine.clear();
    engine.draw(id, img->srcRect(), img->dstRect());
}