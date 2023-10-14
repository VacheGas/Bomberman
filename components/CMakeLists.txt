add_library(
  components_headers 
  INTERFACE
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
  src/player.cpp
)
      
add_subdirectory(test)
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

target_link_libraries(components_headers INTERFACE core_headers)
target_link_libraries(components PRIVATE core gtest gtest_main)