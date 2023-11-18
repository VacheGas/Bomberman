cmake_minimum_required(VERSION 3.24)
enable_testing()
add_subdirectory(test)

include_directories(
  ${GTEST_DIR}/include
  ${CMAKE_SOURCE_DIR}/src
)

add_executable(player_test player_test.cpp)

target_link_libraries(player_test bomberman_components_testing)

add_test(player player_test COMMAND $<TARGET_FILE:player_test>)

set_target_properties(player_test PROPERTIES
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED YES
  CXX_EXTENSIONS NO
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")