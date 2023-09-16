cmake_minimum_required(VERSION 3.24)
project(tests)

include_directories(
  ${GTEST_DIR}/include
  ${CMAKE_SOURCE_DIR}/src
)

set(
  TEST_FILES
  game_test.cpp
)

add_executable(tests ${TEST_FILES})

target_link_libraries(tests core gtest_main)

set_target_properties(tests PROPERTIES
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED YES
  CXX_EXTENSIONS NO
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")