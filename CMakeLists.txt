# Setup the basic CMake environment
cmake_minimum_required(VERSION 3.20)

project(Spectogram 
    VERSION 1.0.0 
    LANGUAGES CXX
)

# Enforce modern C++ standards
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Define the main target (Build as a library)
add_library(spectogram_lib STATIC 
    src/audio_capture.cpp
    src/processor.cpp
    src/visualizer.cpp
)

# Bind the header search paths to your library target
target_include_directories(spectogram_lib 
    PUBLIC 
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Crucial for static SFML: Tells CMake to use static targets
set(SFML_STATIC_LIBRARIES TRUE)

# Get SFML
find_package(SFML 3.0 COMPONENTS Graphics Window System CONFIG REQUIRED)

target_link_libraries(spectogram_lib PUBLIC 
    SFML::Graphics 
    SFML::Window 
    SFML::System
)

# Tell CMake to output the final executable to your main project root directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}")

# Define the executable application entry point
add_executable(spectogram 
    src/main.cpp
)

# Link your application to your core library logic
target_link_libraries(spectogram 
    PRIVATE 
        spectogram_lib
)
