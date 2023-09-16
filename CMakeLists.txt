cmake_minimum_required(VERSION 3.0)

project(Bomberman)

# Set the C++ standard to use (e.g., C++11, C++14, C++17)
set(CMAKE_CXX_STANDARD 17)

# Find SDL2 package
find_package(SDL2 REQUIRED)
find_package(SDL2_IMAGE REQUIRED)

set(SOURCES main.cpp)

add_subdirectory(googletest)
add_subdirectory(core)

add_executable(${PROJECT_NAME} ${SOURCES})

# Include SDL2 and SDL2_image headers
target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_IMAGE_INCLUDE_DIRS})
include_directories(${CMAKE_SOURCE_DIR}/core)

# Link SDL2 and SDL2_image libraries
target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL2_LIBRARIES})
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2_image::SDL2_image)
target_link_libraries(${PROJECT_NAME} PRIVATE gtest gtest_main)
target_link_libraries(${PROJECT_NAME} PRIVATE core)
