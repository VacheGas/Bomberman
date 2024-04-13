add_subdirectory(test_utils)
add_subdirectory(components)
add_subdirectory(engine)

include_directories(${CMAKE_SOURCE_DIR}/src/engine)
include_directories(${CMAKE_SOURCE_DIR}/src/components)
