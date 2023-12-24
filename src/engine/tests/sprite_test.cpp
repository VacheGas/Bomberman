//
// Created by Vache Gasparyan on 24.12.23.
//
#include "test_utils/gtest_main.hpp"

#include <sprite_factory.hpp>
#include <iostream>
TEST(Sprite, ReadImage) {
    int width = 64;
    int height = 64;
    SDL_Window* _window = SDL_CreateWindow("test", 10, 10, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(_window, nullptr, SDL_RENDERER_ACCELERATED);
    sdl::SpriteFactory::addNewSprite(RESOURCES_PATH "/64x64/Bark.png", 1, renderer);
    std::shared_ptr<sdl::Sprite> sprite = sdl::SpriteFactory::getSprite(1);
    EXPECT_EQ(sprite->width(), width);
    EXPECT_EQ(sprite->height(), height);
}