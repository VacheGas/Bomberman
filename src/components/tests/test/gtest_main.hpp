//
// Created by Vache Gasparyan on 18.11.23.
//

#ifndef BOMBERMAN_GTEST_MAIN_HPP
#define BOMBERMAN_GTEST_MAIN_HPP

#include <gtest/gtest.h>

#define ADD_GTEST_MAIN                          \
    int main(int argc, char** argv) {           \
        ::testing::InitGoogleTest(&argc, argv); \
        return RUN_ALL_TESTS();                 \
    }

#endif //BOMBERMAN_GTEST_MAIN_HPP
