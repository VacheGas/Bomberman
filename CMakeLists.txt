cmake_minimum_required(VERSION 3.0)

project(Bomberman)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -fsanitize=undefined,address -Wall -Wextra -Werror")
set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -g -fsanitize=undefined,address -Wall -Wextra -Werror")

set(SOURCES main.cpp)

SET(RESOURCES_PATH "${CMAKE_CURRENT_SOURCE_DIR}/assets")

if(APPLE)
    enable_language(OBJC)
endif()

add_subdirectory(dependencies/googletest)
add_subdirectory(dependencies/SDL)
add_subdirectory(dependencies/SDL_image)
add_subdirectory(dependencies/json)

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_SOURCE_DIR}/cmake")

include(add_test)
add_subdirectory(src)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE engine)
