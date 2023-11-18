cmake_minimum_required(VERSION 3.24)
enable_testing()

include_directories(
        ${GTEST_DIR}/include
        ${CMAKE_SOURCE_DIR}/src
)

add_executable(engine_test engine_test.cpp)
target_link_libraries(engine_test bomberman_engine_testing)

set_target_properties(engine_test PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")