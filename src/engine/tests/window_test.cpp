//
// Created by Vache Gasparyan on 13.01.24.
//

#include "test_utils/gtest_main.hpp"

#include <engine/window.hpp>

TEST(Window, Get) {
    std::string_view title("test_name");
    sdl::Window window = sdl::Window(title, 300, 160, 0);

    EXPECT_EQ(window.flags(), 0);
    EXPECT_EQ(window.width(), 300);
    EXPECT_EQ(window.height(), 160);
    EXPECT_EQ(window.title(), title);
}