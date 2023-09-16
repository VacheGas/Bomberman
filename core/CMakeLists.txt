add_library(
  core_headers 
  INTERFACE
  include/core/game.hpp
)
  
target_include_directories(
  core_headers 
  INTERFACE
  include/
)
    
add_library(
  core
  STATIC
  src/game.cpp
)
      
add_subdirectory(test)
enable_testing()

target_link_libraries(
  core
  PUBLIC
  core_headers
)

target_link_libraries(
  core_headers
  INTERFACE
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

# Find SDL2 package
find_package(SDL2 REQUIRED)
find_package(SDL2_IMAGE REQUIRED)

# Include SDL2 and SDL2_image headers
target_include_directories(core_headers INTERFACE ${SDL2_INCLUDE_DIRS})
target_include_directories(core_headers INTERFACE ${SDL2_IMAGE_INCLUDE_DIRS})

# Link SDL2 and SDL2_image libraries
target_link_libraries(core PRIVATE ${SDL2_LIBRARIES})
target_link_libraries(core PRIVATE SDL2_image::SDL2_image)
target_link_libraries(core PRIVATE gtest gtest_main)