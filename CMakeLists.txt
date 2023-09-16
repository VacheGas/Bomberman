cmake_minimum_required(VERSION 3.0)

project(YourProjectName)

# Set the C++ standard to use (e.g., C++11, C++14, C++17)
set(CMAKE_CXX_STANDARD 17)

# Find SDL2 package
find_package(SDL2 REQUIRED)
find_package(SDL2_IMAGE REQUIRED)

# Add your source files
set(SOURCES
        main.cpp
        # Add your other source files here
)

# Create the executable

add_executable(${PROJECT_NAME} ${SOURCES})

# Include SDL2 headers
target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_IMAGE_INCLUDE_DIRS})

# Link SDL2 libraries
target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL2_LIBRARIES} SDL2_image::SDL2_image)

