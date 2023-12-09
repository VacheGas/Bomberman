cmake_minimum_required(VERSION 3.0)

project(Bomberman)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

set(SOURCES main.cpp)

SET(RESOURCES_PATH "${CMAKE_CURRENT_SOURCE_DIR}/assets")

if(APPLE)
    enable_language(OBJC)
endif()

add_subdirectory(dependencies/googletest)
add_subdirectory(dependencies/SDL)
add_subdirectory(dependencies/SDL_image)

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_SOURCE_DIR}/cmake")

include(add_test)
add_subdirectory(src)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE engine)
