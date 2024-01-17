add_library(
  engine_headers
  INTERFACE
  include/engine/engine.hpp
  include/engine/graphic_element.hpp
  include/engine/generate_id.hpp
  include/engine/sdlTextureDeleter.hpp
  include/engine/sprite.hpp
  include/engine/sprite_factory.hpp
  include/engine/vec.hpp
)
  
target_include_directories(
  engine_headers 
  INTERFACE
  include/
)
    
add_library(
  engine
  STATIC
  src/engine.cpp
  src/sprite.cpp
  src/graphic_element.cpp
  src/sprite_factory.cpp
)

target_link_libraries(
  engine
  PUBLIC
  engine_headers
)

target_link_libraries(
  engine_headers
  INTERFACE
)

add_subdirectory(tests)
enable_testing()

target_include_directories(
  engine_headers INTERFACE 
  ${SDL3_SOURCE_DIR}/include 
  ${SDL3_SOURCE_DIR}/include/SDL3 
  ${SDL3_image_SOURCE_DIR}/include 
  ${SDL3_image_SOURCE_DIR}/include/SDL3_image
  ${CMAKE_SOURCE_DIR}/dependencies/json
  ${CMAKE_SOURCE_DIR}/dependencies/json/include
)

target_link_libraries(
  engine 
  PRIVATE 
  SDL3::SDL3
  SDL3_image::SDL3_image
  nlohmann_json::nlohmann_json
)