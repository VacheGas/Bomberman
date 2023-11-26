cmake_minimum_required(VERSION 3.0)

project(Bomberman)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

set(SOURCES main.cpp)

if(APPLE)
    enable_language(OBJC)
endif()

add_subdirectory(dependencies/googletest)
add_subdirectory(dependencies/SDL)
add_subdirectory(dependencies/SDL_image)

add_subdirectory(src)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE engine)
