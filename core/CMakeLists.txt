add_library(
    core_headers 
    INTERFACE 
    include/core/color.hpp
    include/core/singleton.hpp
)

target_include_directories(
    core_headers
    INTERFACE
    include/
)

add_library(
    core
    STATIC
    src/color.cpp
)

target_link_libraries(
    core
    PUBLIC
    core_headers
)