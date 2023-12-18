add_library(
		engine_headers
		INTERFACE
		include/animatable_graphic_element.hpp
		include/engine.hpp
		include/graphic_element.hpp
		include/sdlTextureDeleter.hpp
		include/sprite.hpp
		include/sprite_factory.hpp
		include/vec.hpp
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
  src/animatable_graphic_element.cpp
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
)

target_link_libraries(
  engine 
  PRIVATE 
  SDL3::SDL3
  SDL3_image::SDL3_image
)