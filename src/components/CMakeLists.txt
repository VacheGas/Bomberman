add_library(
  components_headers 
  INTERFACE
  include/components/input_handler_publisher.hpp
  include/components/menu.hpp
  include/components/player.hpp
)
  
target_include_directories(
  components_headers 
  INTERFACE
  include/
)
    
add_library(
  components
  STATIC
  src/input_handler_publisher.cpp
  src/menu.cpp
  src/player.cpp
)
      
add_subdirectory(tests)
enable_testing()

target_link_libraries(
  components
  PUBLIC
  components_headers
)

target_link_libraries(
  components_headers
  INTERFACE
)

target_link_libraries(components_headers INTERFACE engine_headers)
target_link_libraries(components PRIVATE engine gtest gtest_main)
target_compile_definitions(components PRIVATE RESOURCES_PATH="${RESOURCES_PATH}")