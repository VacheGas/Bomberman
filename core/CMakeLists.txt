add_library(
  core_headers 
  INTERFACE
  include/core/color.hpp
  include/core/exception.hpp
  include/core/game.hpp
  include/core/game_object.hpp
  include/core/sprite.hpp
  include/core/texture_manager.hpp
)
  
target_include_directories(
  core_headers 
  INTERFACE
  include/
)
    
add_library(
  core
  STATIC
  src/exception.cpp
  src/game.cpp
  src/texture_manager.cpp
)

target_link_libraries(
  core
  PUBLIC
  core_headers
)

target_link_libraries(
  core_headers
  INTERFACE
)

add_subdirectory(test)
enable_testing()

target_include_directories(
  core_headers INTERFACE 
  ${SDL3_SOURCE_DIR}/include 
  ${SDL3_SOURCE_DIR}/include/SDL3 
  ${SDL3_image_SOURCE_DIR}/include 
  ${SDL3_image_SOURCE_DIR}/include/SDL3_image
)

target_link_libraries(
  core_headers
  INTERFACE
  core_headers
)

target_link_libraries(
  core 
  PRIVATE 
  SDL3::SDL3
  SDL3_image::SDL3_image
)