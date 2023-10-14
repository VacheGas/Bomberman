add_library(
  game_headers 
  INTERFACE
  include/game/game.hpp
)
  
target_include_directories(
  game_headers 
  INTERFACE
  include/
)
    
add_library(
  game
  STATIC
  src/game.cpp
)
      
add_subdirectory(test)
enable_testing()

target_link_libraries(
  game
  PUBLIC
  game_headers
)

target_link_libraries(
  game_headers
  INTERFACE
)

target_link_libraries(game PRIVATE engine gtest gtest_main)