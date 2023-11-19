cmake_minimum_required(VERSION 3.24)
add_subdirectory(test)
enable_testing()

include_directories(
  ${GTEST_DIR}/include
  ${CMAKE_SOURCE_DIR}/src
)

bomberman_add_test(
        NAME bomberman_player_test
        SRCS player_test.cpp
        DEPS bomberman_components_testing
)
