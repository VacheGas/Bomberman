add_library(
    core_headers 
    INTERFACE 
    include/core/singleton.hpp
)

target_include_directories(
    core_headers
    INTERFACE
    include/
)