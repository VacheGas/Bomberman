add_library(
  game_headers 
  INTERFACE
  include/game/game_object.hpp
  include/game/game.hpp
  include/game/sprite.hpp
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
  src/sprite.cpp
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

target_link_libraries(game_headers INTERFACE engine_headers)
target_link_libraries(game PRIVATE engine gtest gtest_main)