add_library(
  engine_headers 
  INTERFACE
  include/engine/color.hpp
  include/engine/exception.hpp
  include/engine/engine.hpp
  include/engine/texture_manager.hpp
)
  
target_include_directories(
  engine_headers 
  INTERFACE
  include/
)
    
add_library(
  engine
  STATIC
  src/color.cpp
  src/engine.cpp
  src/exception.cpp
  src/texture_manager.cpp
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

target_include_directories(
  engine_headers INTERFACE 
  ${SDL3_SOURCE_DIR}/include 
  ${SDL3_SOURCE_DIR}/include/SDL3 
  # ${SDL3_image_SOURCE_DIR}/include 
  # ${SDL3_image_SOURCE_DIR}/include/SDL3_image
)

target_link_libraries(engine PRIVATE SDL3::SDL3)
# target_link_libraries(graphics PRIVATE SDL3_image::SDL3_image)